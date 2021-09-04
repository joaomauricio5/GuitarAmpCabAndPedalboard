//
//  ReverbAudio.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//

#pragma once

#include "JuceHeader.h"

/** Class for the audio processing that the Reverb pedal performs, using an instance of dsp::Reverb. The reverb parameters (wet, room size, damping, stereo width) are held by an instance of Reverb::Parameters */

class ReverbAudio : public dsp::ProcessorBase
{
public:
    
    /** ReverbAudio constructor*/
    ReverbAudio();
    
    /** Initialises the dsp::Reverb object
    @param spec holds information such as number of channels to process, sample rate and maximum block size
    */
    void prepare (const dsp::ProcessSpec& spec) override;
    
    /** Processes the input samples supplied in the context through the dsp::Reverb object
    @param context contains the input and output samples to be processed
    */
    void process (const dsp::ProcessContextReplacing<float> &context) override;
    
    /** Resets the dsp::Reverb instance internal state*/
    void reset() override;
    
    std::atomic<float> wetValue;
    std::atomic<float> roomSizeValue;
    std::atomic<float> dampingValue;
    std::atomic<float> stereoWidthValue;
    
    /** Holds all of the parameters for the dsp::Reverb object to use*/
    Reverb::Parameters reverbParameters;
    
private:
    
    /** Updates wetValue, roomSizeValue, dampingValue and  stereoWidthValue in a thread-safe way for the dsp::Reverb object to use through Reverb::Parameters, which can be changed through the UI*/
    void updateValuesFromUI();

    dsp::Reverb reverb;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbAudio)
};

