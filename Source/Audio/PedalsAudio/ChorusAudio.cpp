//  ChorusAudio.cpp
//  AudioDeviceManagerTutorial - App
//
//  Created by João Mauricio UWE ID 18030724 on 17/01/2021.
//  Copyright © 2021 JUCE. All rights reserved.

#include "ChorusAudio.h"


ChorusAudio::ChorusAudio()
{
    chorus.setMix(0.5);
    chorus.setRate(1.0);
    chorus.setDepth(0.25);
}

void ChorusAudio::prepare (const dsp::ProcessSpec& spec)
{
    chorus.prepare(spec);
}

void ChorusAudio::process (const dsp::ProcessContextReplacing<float> &context) 
{
    updateValuesFromUI();
    chorus.process(context);
}

void ChorusAudio::reset()
{
    chorus.reset();
}

void ChorusAudio::updateValuesFromUI()
{
    chorus.setMix(mixValue.load());
    chorus.setRate(rateValue.load());
    chorus.setDepth(depthValue.load());
}

