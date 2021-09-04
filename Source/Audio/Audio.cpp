#include "Audio.h"

Audio::Audio() : deviceManager (defaultDeviceManager),
usingCustomDeviceManager (false)

{
    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2, nullptr); });
    }
    else
    {
        setAudioChannels (1, 2, nullptr);
    }
    
    // default pedal choices
    pedalAudio[0] = &noiseGate;
    pedalAudio[1] = &overdriveDistortion;
    pedalAudio[2] = &chorus;
    pedalAudio[3] = &reverb;
    //
}

Audio::~Audio()
{
    shutdownAudio();
}

ChorusAudio* Audio::getChorusAudio() {return &chorus;}

PhaserAudio* Audio::getPhaserAudio() {return &phaser;}

ReverbAudio* Audio::getReverbAudio() {return &reverb;}

OverdriveAudio* Audio::getOverdriveDistortionAudio() {return &overdriveDistortion;}

FuzzAudio* Audio::getFuzzDistortionAudio() {return &fuzzDistortion;}

NoiseGateAudio* Audio::getNoiseGate() {return &noiseGate;}

AmpAudio* Audio::getAmp() {return &amp;}

CabSimulatorAudio* Audio::getCabSimulator() {return &cabSimulator;}

DelayAudio* Audio::getDelay() {return &delay;}


void Audio::setPedal(int pedalIndexToChange, PedalsAvailable pedalToChangeTo)
{
    switch (pedalToChangeTo)
    {
        case Chorus:
            pedalAudio[pedalIndexToChange] = &chorus;
            break;
            
        case Reverb:
            pedalAudio[pedalIndexToChange] = &reverb;
            break;
            
        case Overdrive:
            pedalAudio[pedalIndexToChange] = &overdriveDistortion;
            break;
            
        case NoiseGate:
            pedalAudio[pedalIndexToChange] = &noiseGate;
            break;
            
        case Delay:
            pedalAudio[pedalIndexToChange] = &delay;
            break;
            
        case Fuzz:
            pedalAudio[pedalIndexToChange] = &fuzzDistortion;
            break;
            
        case Phaser:
            pedalAudio[pedalIndexToChange] = &phaser;
            break;
            
        default:
            break;
    }
}

void Audio::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // Creating a dsp::ProcessSpec instance to use to prepare the dsp processors
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlockExpected;
    spec.numChannels = 2;
    //
    
    amp.prepare(spec);
    chorus.prepare(spec);
    phaser.prepare(spec);
    reverb.prepare(spec);
    noiseGate.prepare(spec);
    delay.prepare(spec);
    overdriveDistortion.prepare(spec);
    fuzzDistortion.prepare(spec);
    cabSimulator.prepare(spec);
    outputLimiter.prepare(spec);
}


void Audio::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    auto* device = deviceManager.getCurrentAudioDevice();
    
    auto activeInputChannels  = device->getActiveInputChannels();
    auto activeOutputChannels = device->getActiveOutputChannels();
    
    auto maxInputChannels  = activeInputChannels.countNumberOfSetBits();
    auto maxOutputChannels = activeOutputChannels.countNumberOfSetBits();
    
    for (auto channel = 0; channel < maxOutputChannels; ++channel)
    {
        if ((! activeOutputChannels[channel]) || maxInputChannels == 0)
        {
            bufferToFill.buffer->clear (channel, bufferToFill.startSample, bufferToFill.numSamples);
        }
        else
        {
            auto actualInputChannel = channel % maxInputChannels; // If there is 1 input, the stereo output is equal in both channels. If there are 2 inputs, the stereo output is true stereo
            
            auto* inBuffer  = bufferToFill.buffer->getReadPointer  (actualInputChannel,
                                                                    bufferToFill.startSample);
            auto* outBuffer = bufferToFill.buffer->getWritePointer (channel, bufferToFill.startSample);
            
            for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
            {
                outBuffer[sample] = inBuffer[sample] ;
            }
        }
    }
    
    // These two variables are created in order to make AudioSourceChannelInfo compatible with the dsp processors' process() function argument
    dsp::AudioBlock<float> block (*bufferToFill.buffer);
    dsp::ProcessContextReplacing<float> context (block) ;
    //
    
    if (isPedalToggleOn[0].load())
        pedalAudio[0].load()->process(context);
    
    if (isPedalToggleOn[1].load())
        pedalAudio[1].load()->process(context);
    
    if (isPedalToggleOn[2].load())
        pedalAudio[2].load()->process(context);
    
    if (isPedalToggleOn[3].load())
        pedalAudio[3].load()->process(context);
    
    amp.process(context);
    
    cabSimulator.process(context);
    
    outputLimiter.process(context);
}


void Audio::releaseResources() 
{
    chorus.reset();
    phaser.reset();
    reverb.reset();
    overdriveDistortion.reset();
    fuzzDistortion.reset();
    noiseGate.reset();
    delay.reset();
    amp.reset();
    cabSimulator.reset();
    outputLimiter.reset();
}


void Audio::setAudioChannels (int numInputChannels, int numOutputChannels, const XmlElement* const xml)
{
 //Copied from AudioAppComponent::setAudioChannels() to request input and output channels from the AudioDeviceManager
    String audioError;
    
    if (usingCustomDeviceManager && xml == nullptr)
    {
        auto setup = deviceManager.getAudioDeviceSetup();
        
        if (setup.inputChannels.countNumberOfSetBits() != numInputChannels
            || setup.outputChannels.countNumberOfSetBits() != numOutputChannels)
        {
            setup.inputChannels.clear();
            setup.outputChannels.clear();
            
            setup.inputChannels.setRange (0, numInputChannels, true);
            setup.outputChannels.setRange (0, numOutputChannels, true);
            
            audioError = deviceManager.setAudioDeviceSetup (setup, false);
        }
    }
    else
    {
        audioError = deviceManager.initialise (numInputChannels, numOutputChannels, xml, true);
    }
    
    jassert (audioError.isEmpty());
    
    deviceManager.addAudioCallback (&audioSourcePlayer);
    audioSourcePlayer.setSource (this);
}

void Audio::shutdownAudio()
{
    audioSourcePlayer.setSource (nullptr);
    deviceManager.removeAudioCallback (&audioSourcePlayer);
    
    // other audio callbacks may still be using the device
    if (! usingCustomDeviceManager)
        deviceManager.closeAudioDevice();
}



