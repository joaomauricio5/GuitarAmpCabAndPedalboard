//
//  FuzzAudio.cpp
//  SDAassignment - App
//
//  Created by João Mauricio UWE ID 18030724 on 15/02/2021.
//

#include "FuzzAudio.h"


FuzzAudio::FuzzAudio()
{
    setTransferFunctionToUse();
}

FuzzAudio::~FuzzAudio()
{
    
}

void FuzzAudio::setTransferFunctionToUse()
{
    waveshaper.functionToUse = [] (float x)
    {
        return jlimit (float (-0.5), float (0.5), x);
    };
}

