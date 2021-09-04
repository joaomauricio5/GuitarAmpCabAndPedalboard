//
//  NoiseGateUI.cpp
//  SDAassignment - App
//
//  Created by João Mauricio UWE ID 18030724 on 09/02/2021.
//

#include "NoiseGateUI.h"

NoiseGateUI::NoiseGateUI() : Pedal(1)
{
    sliderLabel[0]->setText("Threshold", dontSendNotification);
    slider[0]->setRange(-60.0, -2.0);
    slider[0]->setValue(-60.0);
}

void NoiseGateUI::setNoiseGateToControl (NoiseGateAudio* noiseGate)
{
    noiseGateAudio = noiseGate;
}

void NoiseGateUI::paint (Graphics& g)
{
    g.setColour (Colours::silver);
    g.fillAll();
}

void NoiseGateUI::sliderValueChanged (Slider* sliderReceived)
{
    auto sliderValue = sliderReceived->getValue();
    
    if (sliderReceived == slider[0])
    {
        noiseGateAudio->thresholdValue = sliderValue;
    }
}
