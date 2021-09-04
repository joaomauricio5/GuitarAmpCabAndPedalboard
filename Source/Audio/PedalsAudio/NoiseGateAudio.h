//
//  NoiseGateAudio.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//

#pragma once
#include "JuceHeader.h"

/** Class for the audio processing that the NoiseGate pedal performs, using an instance of dsp::NoiseGate. */

class NoiseGateAudio : public dsp::ProcessorBase
{
public:
    
    /** NoiseGateAudio constructor*/
    NoiseGateAudio();
    
    /** Initialises the dsp::NoiseGate object
    @param spec holds information such as number of channels to process, sample rate and maximum block size
    */
    void prepare (const dsp::ProcessSpec& spec) override;
    
    /** Processes the input samples supplied in the context through the dsp::NoiseGate object
    @param context contains the input and output samples to be processed
    */
    void process (const dsp::ProcessContextReplacing<float> &context) override;
    
    /** Resets the dsp::NoiseGate instance internal state*/
    void reset() override;
    
    std::atomic<float> thresholdValue;
    
private:
    
    dsp::NoiseGate<float> noiseGate;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseGateAudio)
};
