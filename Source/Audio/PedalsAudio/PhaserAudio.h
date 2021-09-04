//
//  PhaserAudio.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//

#pragma once

#include "JuceHeader.h"

/** Class for the audio processing that the Phaser pedal performs, using an instance of dsp::Phaser. */

class PhaserAudio : public dsp::ProcessorBase
{
public:
    /** PhaserAudio constructor*/
    PhaserAudio();
    
    /** Initialises the dsp::Phaser object
    @param spec holds information such as number of channels to process, sample rate and maximum block size
    */
    void prepare (const dsp::ProcessSpec& spec) override;
    
    /** Processes the input samples supplied in the context through the dsp::Phaser object
    @param context contains the input and output samples to be processed
    */
    void process (const dsp::ProcessContextReplacing<float>&context) override;
    
    /** Resets the dsp::Phaser instance internal state*/
    void reset() override;
    
    std::atomic<float> mixValue;
    std::atomic<float> rateValue;
    std::atomic<float> depthValue;
    
private:
    /** Updates mixValue, rateValue and depthValue in a thread-safe way for the dsp::Phaser object to use, which can be changed through the UI*/
    void updateValuesFromUI();

    dsp::Phaser<float> phaser;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaserAudio)
};
