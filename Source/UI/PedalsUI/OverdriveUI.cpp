//
//  OverdriveUI.cpp
//  SDAassignment - App
//
//  Created by João Mauricio UWE ID 18030724 on 15/02/2021.

#include "OverdriveUI.h"

OverdriveUI::OverdriveUI()
{
    slider[0]->setRange (1.0,80.0);
    slider[0]->setValue (40.0);
    sliderLabel[0]->setText("Overdrive", dontSendNotification);
}

void OverdriveUI::setDistortionToControl (OverdriveAudio* overdrive)
{
    overdriveAudio = overdrive;
}

void OverdriveUI::paint (Graphics& g)
{
    g.setColour (Colours::mediumpurple);
    g.fillAll();
}

void OverdriveUI::sliderValueChanged (Slider* sliderReceived)
{
    auto sliderValue = sliderReceived->getValue();
    
    if (sliderReceived == slider[0])
        overdriveAudio->preGainValue = sliderValue;
    
    else if (sliderReceived == slider[1])
        overdriveAudio->postGainValue = sliderValue;
}
