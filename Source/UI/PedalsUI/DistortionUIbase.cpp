//  DistortionUI.cpp
//  SDAassignment - App
//
//  Created by João Mauricio UWE ID 18030724 on 06/02/2021.
//

#include "DistortionUIbase.h"

DistortionUIbase::DistortionUIbase() : Pedal(2)
{
    slider[0]->setRange (1.0,80.0);
    slider[0]->setValue(1.0);
    slider[1]->setRange(0.0, 0.5);
    slider[1]->setValue(0.1);
    
    sliderLabel[0]->setText("Drive", dontSendNotification);
    sliderLabel[1]->setText("Output", dontSendNotification);
}

void DistortionUIbase::resized()
{
    pedalToggle.setBounds(getWidth()/2 - 12.5, getHeight()*0.9, 25, 25);
    
    auto rect = getLocalBounds();
    
    auto rect2 = rect;
    
    rect.removeFromBottom(getHeight()/2);
    rect.removeFromBottom(20);
    rect.removeFromTop(40);
    
    slider[0]->setBounds(rect);
    
    rect2.removeFromTop(getHeight()/2);
    rect2.removeFromTop(20);
    rect2.removeFromBottom(40);
    slider[1]->setBounds(rect2);
}
