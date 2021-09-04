//  DistortionAudio.cpp
//  AudioDeviceManagerTutorial - App
//
//  Created by João Mauricio UWE ID 18030724 on 17/01/2021.
//  Copyright © 2021 JUCE. All rights reserved.
//

#include "DistortionAudioBase.h"


DistortionAudioBase::DistortionAudioBase()
{
    preGain.setGainLinear(1.0);
    postGain.setGainLinear(1.0);
}

DistortionAudioBase::~DistortionAudioBase()
{
    
}

void DistortionAudioBase::prepare (const dsp::ProcessSpec& spec)
{
    preGain.prepare(spec);
    postGain.prepare(spec);
    waveshaper.prepare (spec);
}

void DistortionAudioBase::process (const dsp::ProcessContextReplacing<float> &context)
{
    preGain.setGainLinear(preGainValue.load());
    postGain.setGainLinear(postGainValue.load());
    preGain.process(context);
    waveshaper.process (context);
    postGain.process(context);
}

void DistortionAudioBase::reset()
{
    preGain.reset();
    waveshaper.reset();
    postGain.reset();
}
