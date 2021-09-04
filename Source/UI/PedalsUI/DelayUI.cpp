//
//  DelayUI.cpp
//  SDAassignment - App
//
//  Created by João Mauricio UWE ID 18030724 on 09/02/2021.


#include "DelayUI.h"


DelayUI::DelayUI()  :   Pedal(2)
{
    sliderLabel[0]->setText("Delay", dontSendNotification);
    slider[0]->setRange(1000, 20000, 1);
    slider[0]->setValue(20000);
    
    sliderLabel[1]->setText("Feedback", dontSendNotification);
    slider[1]->setRange(0.1,1);
    slider[1]->setValue(0.1);
}

void DelayUI::setDelayToControl (DelayAudio* delay)
{
    delayAudio = delay;
}

void DelayUI::paint (Graphics& g)
{
    g.setColour (Colours::purple);
    g.fillAll();
}

void DelayUI::sliderValueChanged (Slider* sliderReceived) 
{
    auto sliderValue = sliderReceived->getValue();
    
    if (sliderReceived == slider[0])
        delayAudio->delayInSamples = sliderValue;
    
    else if (sliderReceived == slider[1])
        delayAudio->feedbackAmount = sliderValue;
}

