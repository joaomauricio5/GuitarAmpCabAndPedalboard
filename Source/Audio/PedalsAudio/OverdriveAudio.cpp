//
//  OverdriveAudio.cpp
//  SDAassignment - App
//
//  Created by João Mauricio UWE ID 18030724 on 15/02/2021.
//

#include "OverdriveAudio.h"

OverdriveAudio::OverdriveAudio()
{
    setTransferFunctionToUse();
}

OverdriveAudio::~OverdriveAudio() {};

void OverdriveAudio::setTransferFunctionToUse()
{
    waveshaper.functionToUse = [] (float x)
    {
        return std::tanh (x);
    };
}
