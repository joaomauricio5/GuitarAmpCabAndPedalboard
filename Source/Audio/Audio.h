//
//  Audio.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//

#pragma once

#include <JuceHeader.h>
#include "PedalsAudio/ReverbAudio.h"
#include "PedalsAudio/ChorusAudio.h"
#include "PedalsAudio/PhaserAudio.h"
#include "PedalsAudio/NoiseGateAudio.h"
#include "PedalsAudio/DelayAudio.h"
#include "PedalsAudio/OverdriveAudio.h"
#include "PedalsAudio/FuzzAudio.h"
#include "CabSimulatorAudio.h"
#include "AmpAudio.h"
#include "OutputLimiter.cpp"

/**Brings all of the audio processing together in the getNextAudioBlock() callback. Current processing chain is pedal1, pedal2, pedal3, pedal4, amp, cab simulator and output limiter*/

class Audio  :  public AudioSource
{
public:
    /**Audio constructor*/
    Audio();
    
    /**Audio destructor*/
    ~Audio() override;
    
    /**Number of pedals to process the audio input through*/
    enum
     {
         NumberOfPedals = 4
     };
     
    /**Pedals available to process audio in this project*/
     enum PedalsAvailable
     {
         Chorus,
         Reverb,
         Overdrive,
         NoiseGate,
         Delay,
         Fuzz,
         Phaser
     };
    
    /**Returns the audio object for the ChorusUI to control
     @return pointer to the ChorusAudio object */
    ChorusAudio* getChorusAudio();
    
    /**Returns the audio object for the PhaserUI to control
    @return pointer to the PhaserAudio object */
    PhaserAudio* getPhaserAudio();
    
    /**Returns the audio object for the ReverbUI to control
    @return pointer to the ReverbAudio object */
    ReverbAudio* getReverbAudio();
    
    /**Returns the audio object for the OverdriveUI to control
    @return pointer to the OverdriveAudio object */
    OverdriveAudio* getOverdriveDistortionAudio();
    
    /**Returns the audio object for the FuzzUI to control
    @return pointer to the FuzzAudio object */
    FuzzAudio* getFuzzDistortionAudio();
    
    /**Returns the audio object for the NoiseGateUI to control
    @return pointer to the NoiseGateAudio object */
    NoiseGateAudio* getNoiseGate();
    
    /**Returns the audio object for the AmpUI to control
    @return pointer to the AmpAudio object */
    AmpAudio* getAmp();
    
    /**Returns the audio object for the CabSimulatorUI to control
    @return pointer to the CabSimulatorAudio object */
    CabSimulatorAudio* getCabSimulator();
    
    /**Returns the audio object for the DelayUI to control
    @return pointer to the DelayAudio object */
    DelayAudio* getDelay();
    
    
    /**Sets the pedalAudio[pedalIndexToChange] to be another pedalAudio instead
    @param pedalIndexToChange index of the pedalAudio to change
    @param pedalToChangeTo type of audio pedal to change pedalAudio[pedalIndexToChange] to*/
    void setPedal(int pedalIndexToChange, PedalsAvailable pedalToChangeTo);
    
    /**Holds the toggle state of each of the 4 pedals in the interface, to determine if a specific slot should be bypassed in the audio processing*/
    std::atomic<bool> isPedalToggleOn[NumberOfPedals];
    
    AudioDeviceManager& deviceManager;
    
private:
    
    /**Tells the audio source to prepare for playing
     @param samplesPerBlockExpected  number of samples that the source will be expected to supply each time its getNextAudioBlock() method is called.
     @param sampleRate  sample rate that the output will be used at */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    
    /** Called repeatedly to fetch subsequent blocks of audio data
    @param bufferToFill  contains the input and output buffers, along with other information*/
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    
    /** Allows the audio source to release anything it no longer needs after playback has stopped.*/
    void releaseResources() override;
    
    /** Copied from AudioAppComponent::setAudioChannels() to request input and output channels from the AudioDeviceManager
     @param numInputChannels number of input channels to request
     @param numOutputChannels number of output channels to request.*/
    void setAudioChannels (int numInputChannels, int numOutputChannels, const XmlElement* const xml);
    
    /** Copied from AudioAppComponent::shutdownAudio() to shut down the audio device and clear the audio source.*/
    void shutdownAudio();
    
    std::atomic<dsp::ProcessorBase*> pedalAudio[NumberOfPedals];
    
    ReverbAudio reverb;
    ChorusAudio chorus;
    PhaserAudio phaser;
    OverdriveAudio overdriveDistortion;
    FuzzAudio fuzzDistortion;
    NoiseGateAudio noiseGate;
    DelayAudio delay;
    
    CabSimulatorAudio cabSimulator;
    AmpAudio amp;
    OutputLimiter outputLimiter;
    
    AudioDeviceManager defaultDeviceManager;
    AudioSourcePlayer audioSourcePlayer;
    bool usingCustomDeviceManager;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Audio)
};

