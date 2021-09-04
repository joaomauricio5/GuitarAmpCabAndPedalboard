//
//  PhaserAudio.cpp
//  SDAassignment - App
//
//  Created by João Mauricio UWE ID 18030724 on 15/02/2021.
//

#include "PhaserAudio.h"


PhaserAudio::PhaserAudio()
{
    
}

void PhaserAudio::prepare (const dsp::ProcessSpec& spec)
{
    phaser.prepare(spec);
}

void PhaserAudio::process (const dsp::ProcessContextReplacing<float>&context)
{
    updateValuesFromUI();
    phaser.process(context);
}

void PhaserAudio::reset()
{
    phaser.reset();
}

void PhaserAudio::updateValuesFromUI()
{
    phaser.setMix(mixValue.load());
    phaser.setRate(rateValue.load());
    phaser.setDepth(depthValue.load());
}
