//
//  AmpAudio.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//

#pragma once

#include "JuceHeader.h"

/** Class for the audio processing that the Amp performs. It uses a dsp::ProcessorChain that consists of gain and three filters. */

class AmpAudio

{
public:
    /** DistortionAudioBase constructor*/
    AmpAudio();
    
    /** Initialises the dsp processors in the dsp::ProcessorChain object
    @param spec holds information such as number of channels to process, sample rate and maximum block size
    */
    void prepare (const dsp::ProcessSpec& spec);
    
    /** Processes the input samples supplied in the context through the processing chain (gain, low shelf filter, mids peak filter and high shelf filter)
    @param context contains the input and output samples to be processed
    */
    void process (dsp::ProcessContextReplacing<float> context);
    
    /** Resets the internal state of the dsp processors in the processor chain*/
    void reset();
    
    std::atomic<float> volumeValue;
    std::atomic<float> lowShelfGain;
    std::atomic<float> midsPeakGain;
    std::atomic<float> highShelfGain;
    
private:
    
    float sampleRate;
    
    enum
    {
        volumeIndex,
        lowShelfFilterIndex,
        midsPeakFilterIndex,
        highShelfFilterIndex
    };
    
    using dspProcessorDuplicator = dsp::ProcessorDuplicator<dsp::IIR::Filter<float> ,dsp::IIR::Coefficients<float>>; // creates 2 filters as each channel needs its own filter
    
    dsp::ProcessorChain<  dsp::Gain<float>,
                          dspProcessorDuplicator,
                          dspProcessorDuplicator,
                          dspProcessorDuplicator
                        > processorChain;
    
    dsp::Gain<float>& volume = processorChain.get<volumeIndex>();
    dspProcessorDuplicator& lowShelfFilter = processorChain.get<lowShelfFilterIndex>();
    dspProcessorDuplicator& midsPeakFilter = processorChain.get<midsPeakFilterIndex>();
    dspProcessorDuplicator& highShelfFilter = processorChain.get<highShelfFilterIndex>();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpAudio)
};
