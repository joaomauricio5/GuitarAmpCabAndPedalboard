//
//  PhaserUI.cpp
//  SDAassignment - App
//
//  Created by João Mauricio UWE ID 18030724 on 15/02/2021.
//

#include "PhaserUI.h"


PhaserUI::PhaserUI() : Pedal(3)
{
    sliderLabel[0]->setText("Mix", dontSendNotification);
    slider[0]->setRange(0.0, 0.6);
    slider[0]->setValue(0.3);
    
    sliderLabel[1]->setText("Rate", dontSendNotification);
    slider[1]->setRange(0.1, 5.0);
    slider[1]->setValue(1.0);
    
    sliderLabel[2]->setText("Depth", dontSendNotification);
    slider[2]->setRange(0.1, 0.6);
    slider[2]->setValue(0.25);
}

void PhaserUI::setPhaserToControl (PhaserAudio* phaser)
{
    phaserAudio = phaser;
}

void PhaserUI::paint (Graphics& g)
{
    g.setColour (Colours::seagreen);
    g.fillAll();
}

void PhaserUI::sliderValueChanged (Slider* sliderReceived)
{
    auto sliderValue = sliderReceived->getValue();
    
    if (sliderReceived == slider[0])
        phaserAudio->mixValue = sliderValue;
    
    else if (sliderReceived == slider[1])
        phaserAudio->rateValue = sliderValue;
    
    else if (sliderReceived == slider[2])
        phaserAudio->depthValue = sliderValue;
}
