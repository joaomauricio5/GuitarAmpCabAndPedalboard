//
//  FuzzUI.cpp
//  SDAassignment - App
//
//  Created by João Mauricio UWE ID 18030724 on 15/02/2021.
//

#include "FuzzUI.h"


FuzzUI::FuzzUI()
{
    slider[0]->setRange (2.0,500.0);
    slider[0]->setValue (500.0);
    sliderLabel[0]->setText("Fuzz", dontSendNotification);
}

void FuzzUI::setDistortionToControl (FuzzAudio* fuzz)
{
    fuzzAudio = fuzz;
}

void FuzzUI::paint (Graphics& g)
{
    g.setColour (Colours::rebeccapurple);
    g.fillAll();
}

void FuzzUI::sliderValueChanged (Slider* sliderReceived)
{
    auto sliderValue = sliderReceived->getValue();
    
    if (sliderReceived == slider[0])
        fuzzAudio->preGainValue = sliderValue;
    
    else if (sliderReceived == slider[1])
        fuzzAudio->postGainValue = sliderValue;
}
