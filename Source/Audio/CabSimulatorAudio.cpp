//  CabSimulatorAudio.cpp
//  SDAassignment - App
//
//  Created by João Mauricio UWE ID 18030724 on 07/02/2021.
//

#include "CabSimulatorAudio.h"

/* The Impulse Responses used here were downloaded from the JUCE website https://docs.juce.com/master/tutorial_dsp_convolution.html and
https://youtu.be/t2wVIG8GMAs */

CabSimulatorAudio::CabSimulatorAudio()
{
    cabIRsBinary[0] = BinaryData::Bogner_wav;
    cabIRsBinary[1] = BinaryData::guitar_amp_wav;
    cabIRsBinary[2] = BinaryData::cassette_recorder_wav;
    cabIRsBinary[3] = BinaryData::Orange_wav;
    
    cabIRsBinarySize[0] = &BinaryData::Bogner_wavSize;
    cabIRsBinarySize[1] = &BinaryData::guitar_amp_wavSize;
    cabIRsBinarySize[2] = &BinaryData::cassette_recorder_wavSize;
    cabIRsBinarySize[3] = &BinaryData::Orange_wavSize;
    
    setImpulseResponse(0);
}

void CabSimulatorAudio::setImpulseResponse(int fileIndexChosen)
{
    loadImpulseResponse (cabIRsBinary[fileIndexChosen],
                         *cabIRsBinarySize[fileIndexChosen],
                         dsp::Convolution::Stereo::no,
                         dsp::Convolution::Trim::yes,
                         1300,  // roughly 30ms for a sample rate of 44.1kHz, which is more than enough
                         dsp::Convolution::Normalise::yes);
}

