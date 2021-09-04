//  ReverbAudio.cpp
//  AudioDeviceManagerTutorial - App
//
//  Created by João Mauricio UWE ID 18030724 on 17/01/2021.
//  Copyright © 2021 JUCE. All rights reserved.
//

#include "ReverbAudio.h"

ReverbAudio::ReverbAudio()
{
    
}

void ReverbAudio::prepare (const dsp::ProcessSpec& spec) 
{
    reverb.prepare(spec);
}

void ReverbAudio::process (const dsp::ProcessContextReplacing<float> &context)
{
    updateValuesFromUI();
    reverb.process(context);
}

void ReverbAudio::reset()
{
    reverb.reset();
}

void ReverbAudio::updateValuesFromUI()
{
    reverbParameters.wetLevel = wetValue.load();
    reverbParameters.roomSize = roomSizeValue.load();
    reverbParameters.damping = dampingValue.load();
    reverbParameters.width = stereoWidthValue.load();
    reverb.setParameters(reverbParameters);
}

