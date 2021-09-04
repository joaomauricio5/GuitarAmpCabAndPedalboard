//
//  NoiseGateAudio.cpp
//  SDAassignment - App
//
//  Created by João Mauricio UWE ID 18030724 on 09/02/2021.
//

#include "NoiseGateAudio.h"

NoiseGateAudio::NoiseGateAudio()
{
    
}

void NoiseGateAudio::prepare (const dsp::ProcessSpec& spec)
{
    noiseGate.prepare(spec);
}

void NoiseGateAudio::process (const dsp::ProcessContextReplacing<float> &context)
{
    noiseGate.setThreshold(thresholdValue.load());
    noiseGate.process(context);
}

void NoiseGateAudio::reset()
{
    noiseGate.reset();
}

