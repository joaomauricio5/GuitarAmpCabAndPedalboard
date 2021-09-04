//  Pedal.cpp
//  AudioDeviceManagerTutorial - App
//
//  Created by João Mauricio UWE ID 18030724 on 17/01/2021.
//  Copyright © 2021 JUCE. All rights reserved.

#include "Pedal.h"

Pedal::Pedal(int numOfSliders)
{
    NumberOfSliders = numOfSliders;
    
    for (int i = 0; i < NumberOfSliders; i++)
    {
        slider.add(new Slider());
        addAndMakeVisible (slider[i]);
        slider[i]->setSliderStyle(Slider::SliderStyle::Rotary);
        slider[i]->setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
        slider[i]->setRange (0.0,1.0);
        slider[i]->addListener(this);
        slider[i]->setNumDecimalPlacesToDisplay(2);
        
        
        sliderLabel.add(new Label());
        addAndMakeVisible (sliderLabel[i]);
        sliderLabel[i]->setText("RenameThisLabel", dontSendNotification);
        sliderLabel[i]->setJustificationType(Justification::Flags::centred);
        sliderLabel[i]->attachToComponent (slider[i], false);
    }
    addAndMakeVisible (pedalToggle);
}


void Pedal::resized()
{
    auto rect = getLocalBounds();
    auto rect2 = rect;
    
    
    pedalToggle.setBounds(getWidth()/2 - 12.5, getHeight()*0.9, 25, 25);
    
    switch (NumberOfSliders)
    {
        case 1:
            slider[0]->centreWithSize(getWidth()/2, getHeight()/2);
            break;
            
        case 2:
            rect.removeFromBottom(getHeight()/2);
            rect.removeFromBottom(15);
            rect.removeFromTop(40);
            
            slider[0]->setBounds(rect);
            
            rect2.removeFromTop(getHeight()/2);
            rect2.removeFromTop(15);
            rect2.removeFromBottom(40);
            
            slider[1]->setBounds(rect2);
            
            break;
            
        case 3:
            rect.removeFromTop(getHeight()/2);
            rect.removeFromTop(15);
            rect.removeFromBottom(40);
            
            slider[0]->setBounds(rect);
            
            rect2.removeFromBottom(getHeight()/2);
            rect2.removeFromTop(40);
            rect2.removeFromBottom(15);
            
            slider[1]->setBounds(rect2.removeFromLeft(getWidth()/2));
            slider[2]->setBounds(rect2);
            
            
            break;
            
        case 4:
            rect.removeFromBottom(10);
            rect.removeFromTop(getHeight()/2);
            rect.removeFromTop(15);
            rect.removeFromBottom(40);
            
            slider[0]->setBounds(rect.removeFromLeft(getWidth()/2));
            slider[1]->setBounds(rect);
            
            rect2.removeFromBottom(10);
            rect2.removeFromBottom(getHeight()/2);
            rect2.removeFromTop(40);
            rect2.removeFromBottom(15);
            
            slider[2]->setBounds(rect2.removeFromLeft(getWidth()/2));
            slider[3]->setBounds(rect2);
            break;
            
        default:
            break;
    }
}

void Pedal::paint (Graphics& g)
{
    g.setColour (Colours::blue);
    g.fillAll();
}

void Pedal::sliderValueChanged (Slider* sliderReceived)
{
    
}
