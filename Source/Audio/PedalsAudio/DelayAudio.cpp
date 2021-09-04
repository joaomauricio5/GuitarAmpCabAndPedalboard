//
//  DelayAudio.cpp
//  SDAassignment - App
//
//  Created by João Mauricio UWE ID 18030724 on 09/02/2021.
//

#include "DelayAudio.h"


DelayAudio::DelayAudio()  : delayLine(20000)
{
    
}

void DelayAudio::prepare (const dsp::ProcessSpec &spec) 
{
    delayLine.prepare(spec);
}

void DelayAudio::reset()
{
    delayLine.reset();
}

void DelayAudio::process (const dsp::ProcessContextReplacing<float> &context)
{
    auto& inputBlock = context.getInputBlock();
    auto& outputBlock = context.getOutputBlock();
    auto numberOfSamples = outputBlock.getNumSamples();
    auto numberOfChannels = outputBlock.getNumChannels();
    
    float delayedSample = 0;
    
    for (auto channel = 0; channel < numberOfChannels; ++channel)
    {
        auto* inBuffer  = inputBlock.getChannelPointer(channel);
        auto* outBuffer = outputBlock.getChannelPointer(channel);
        
        delayLine.setDelay(delayInSamples.load());
        
        for (auto sampleIndex = 0; sampleIndex < numberOfSamples; ++sampleIndex)
        {
            delayedSample = delayLine.popSample(channel, -1, true) * 0.4;
            delayLine.pushSample( channel, inBuffer[sampleIndex] + delayedSample * feedbackAmount.load() );
            outBuffer[sampleIndex] = inBuffer[sampleIndex] + delayedSample;
        }
    }
}


