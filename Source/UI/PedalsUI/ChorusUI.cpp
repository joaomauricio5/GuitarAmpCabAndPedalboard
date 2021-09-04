//  ChorusUI.cpp
//  AudioDeviceManagerTutorial - App
//
//  Created by João Mauricio UWE ID 18030724 on 17/01/2021.
//  Copyright © 2021 JUCE. All rights reserved.
//

#include "ChorusUI.h"

ChorusUI::ChorusUI() : Pedal(3)
{
    sliderLabel[0]->setText("Mix", dontSendNotification);
    slider[0]->setRange(0.0, 0.6);
    slider[0]->setValue(0.3);
    
    sliderLabel[1]->setText("Rate", dontSendNotification);
    slider[1]->setRange(0.1, 2.0);
    slider[1]->setValue(1.0);
    
    sliderLabel[2]->setText("Depth", dontSendNotification);
    slider[2]->setRange(0.1, 0.5);
    slider[2]->setValue(0.25);
}

void ChorusUI::setChorusToControl (ChorusAudio* chorus)
{
    chorusAudio = chorus;
}

void ChorusUI::paint (Graphics& g)
{
    g.setColour (Colours::yellowgreen);
    g.fillAll();
}

void ChorusUI::sliderValueChanged (Slider* sliderReceived)
{
    auto sliderValue = sliderReceived->getValue();
    
    if (sliderReceived == slider[0])
        chorusAudio->mixValue = sliderValue;
    
    else if (sliderReceived == slider[1])
        chorusAudio->rateValue = sliderValue;
    
    else if (sliderReceived == slider[2])
        chorusAudio->depthValue = sliderValue;
}

