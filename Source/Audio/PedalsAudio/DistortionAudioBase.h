//
//  DistortionAudioBase.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//

#pragma once
#include "JuceHeader.h"
/** Base class for the audio processing of the two distortion pedals used (Overdrive and Fuzz).  Its processing chain consists of two dsp::Gain objects (preGain and postGain) and an instance of dsp::WaveShaper*/
class DistortionAudioBase : public dsp::ProcessorBase
{
public:
    /** DistortionAudioBase constructor*/
    DistortionAudioBase();
    
   /** DistortionAudioBase destructor*/
    virtual ~DistortionAudioBase();
    
    /** Initialises the DSP objects
        @param spec holds information such as number of channels to process, sample rate and maximum block size
        */
    void prepare (const dsp::ProcessSpec& spec) override;
    
    /** Processes the input samples supplied in the context through the processing chain (preGain, waveshaper and postGain)
    @param context contains the input and output samples to be processed
    */
    void process (const dsp::ProcessContextReplacing<float> &context) override;
    
    /** Resets the DSP instances internal state*/
    void reset() override;
    
    std::atomic<float> preGainValue;
    std::atomic<float> postGainValue;
    
    dsp::WaveShaper<float> waveshaper;
    
private:
    
    dsp::Gain<float> preGain;
    dsp::Gain<float> postGain;
    
    /** Sets the transfer function for the waveshaper to use*/
    virtual void setTransferFunctionToUse() = 0;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionAudioBase)
};
