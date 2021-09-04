//
//  DelayAudio.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//

#pragma once
#include "JuceHeader.h"

/** Class for the audio processing that the Delay pedal performs, using an instance of dsp::DelayLine. */

class DelayAudio :   public dsp::ProcessorBase
{
public:
    /** DelayAudio constructor*/
    DelayAudio();
    
    /** Initialises the dsp::DelayLine object
    @param spec holds information such as number of channels to process, sample rate and maximum block size
    */
    void prepare (const dsp::ProcessSpec &spec) override;
    
    /** Processes the input samples supplied in the context sample-by-sample through a delay line.
    @param context contains the input and output samples to be processed
    */
    void process (const dsp::ProcessContextReplacing<float> &context) override;
    
    /** Resets the dsp::DelayLine instance internal state*/
    void reset() override;
    
    std::atomic<float> feedbackAmount;
    std::atomic<int> delayInSamples;

private:
    
    dsp::DelayLine<float,  juce::dsp::DelayLineInterpolationTypes::Linear> delayLine;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayAudio)
};

