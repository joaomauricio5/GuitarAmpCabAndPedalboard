//  AmpAudio.cpp
//  SDAassignment - App
//
//  Created by João Mauricio UWE ID 18030724 on 07/02/2021.
//

#include "AmpAudio.h"

AmpAudio::AmpAudio()
{
    volumeValue = 1.0;
    lowShelfGain = 1.0;
    midsPeakGain = 1.0;
    highShelfGain = 1.0;
    volume.setRampDurationSeconds(0.1); // removes clicks due to abrupt volume slider changes
}

void AmpAudio::prepare (const dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;
    processorChain.prepare(spec);
}

void AmpAudio::process (dsp::ProcessContextReplacing<float> context)
{
    // UPDATES VALUES FROM THE UI IN A THREAD-SAFE WAY
    volume.setGainLinear(volumeValue.load());
    *lowShelfFilter.state = *dsp::IIR::Coefficients<float>::makeLowShelf(sampleRate, 400, 0.7, lowShelfGain.load());
    *midsPeakFilter.state = *dsp::IIR::Coefficients<float>::makePeakFilter(sampleRate, 800, 0.3, midsPeakGain.load());
    *highShelfFilter.state = *dsp::IIR::Coefficients<float>::makeHighShelf(sampleRate, 1500, 0.7, highShelfGain.load());
    //
    
    processorChain.process(context);
}

void AmpAudio::reset()
{
    processorChain.reset();
}

