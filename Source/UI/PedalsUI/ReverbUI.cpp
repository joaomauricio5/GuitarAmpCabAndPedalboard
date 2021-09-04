//  ReverbUI.cpp
//  AudioDeviceManagerTutorial - App
//
//  Created by João Mauricio UWE ID 18030724 on 17/01/2021.
//  Copyright © 2021 JUCE. All rights reserved.
//

#include "ReverbUI.h"

ReverbUI::ReverbUI()  :   Pedal(4)
{
    sliderLabel[0]->setText("Room Size", dontSendNotification);
    slider[0]->setValue(0.5);
    
    sliderLabel[1]->setText("Mix", dontSendNotification);
    slider[1]->setValue(0.3);
    
    sliderLabel[2]->setText("Damping", dontSendNotification);
    slider[2]->setValue(0.5);
    
    sliderLabel[3]->setText("Stereo Width", dontSendNotification);
    slider[3]->setValue(1.0);
}

void ReverbUI::setReverbToControl (ReverbAudio* reverb)
{
    reverbAudio = reverb;
}

void ReverbUI::sliderValueChanged (Slider* sliderReceived)
{
    auto sliderValue = sliderReceived->getValue();
    
    if (sliderReceived == slider[0])
        reverbAudio->roomSizeValue = sliderValue;
    
    else if (sliderReceived == slider[1])
        reverbAudio->wetValue = sliderValue;
    
    else if (sliderReceived == slider[2])
        reverbAudio->dampingValue = sliderValue;
    
    else if (sliderReceived == slider[3])
        reverbAudio->stereoWidthValue = sliderValue;
}
