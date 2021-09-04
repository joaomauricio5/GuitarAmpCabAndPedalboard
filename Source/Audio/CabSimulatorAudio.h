//
//  CabSimulatorAudio.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//
#pragma once

#include "JuceHeader.h"

/** Class for the audio processing that the CabSimulator performs, through dsp::Convolution. It has pointers to 4 files from BinaryData that correspond to 4 different Impulse Responses.
 
 The Impulse Responses used were downloaded from the JUCE website https://docs.juce.com/master/tutorial_dsp_convolution.html and
    https://youtu.be/t2wVIG8GMAs */

class CabSimulatorAudio :   public dsp::Convolution
{
public:
    /** CabSimulatorAudio constructor*/
    CabSimulatorAudio();
    
    /** Sets the impulse response to use
     @param fileIndexChosen index from the 4 impulse responses available to use */
    void setImpulseResponse(int fileIndexChosen);
    
private:
    
     /**Array of pointers that will point to the impulse responses stored as BinaryData
      @see BinaryData*/
     const char* cabIRsBinary[4];
    
    /**Array of pointers that will point to the size of the impulse responses stored as BinaryData
    @see cabIRsBinary[4]*/
     const int* cabIRsBinarySize[4];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CabSimulatorAudio)
};
