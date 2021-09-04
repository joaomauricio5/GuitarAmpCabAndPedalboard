//  AmpUI.cpp
//  AudioDeviceManagerTutorial - App
//
//  Created by João Mauricio UWE ID 18030724 on 17/01/2021.
//  Copyright © 2021 JUCE. All rights reserved.
//


#include "AmpUI.h"

AmpUI::AmpUI()
{
    for (int i = 0; i < 3; i++)
    {
        addAndMakeVisible (filterGainSlider[i]);
        filterGainSlider[i].setSliderStyle(Slider::SliderStyle::Rotary);
        filterGainSlider[i].setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 80, 20);
        filterGainSlider[i].setRange (0.1,4.0);
        filterGainSlider[i].setValue(1.0);
        filterGainSlider[i].addListener(this);
        filterGainSlider[i].setNumDecimalPlacesToDisplay(1);
        
        addAndMakeVisible (filterGainLabel[i]);
        filterGainLabel[i].setJustificationType(Justification::Flags::centred);
        filterGainLabel[i].attachToComponent (&filterGainSlider[i], false);
    }
    
    filterGainLabel[0].setText("Bass", dontSendNotification);
    filterGainLabel[1].setText("Mids", dontSendNotification);
    filterGainLabel[2].setText("Treble", dontSendNotification);
    
    addAndMakeVisible (volumeSlider);
    volumeSlider.setRange (0.0,6.0);
    volumeSlider.setValue(1.0);
    volumeSlider.addListener(this);
    volumeSlider.setNumDecimalPlacesToDisplay(1);
    
    addAndMakeVisible (volumeLabel);
    volumeLabel.setJustificationType(Justification::Flags::centred);
    volumeLabel.attachToComponent (&volumeSlider, false);
}

void AmpUI::setAmpToControl (AmpAudio* amp)
{
    ampAudio = amp;
}

void AmpUI::paint (Graphics& g)
{
    g.setColour (Colours::orange);
    g.fillAll();
}

void AmpUI::resized()
{
    auto rect = getLocalBounds();
    
    rect.removeFromTop(30);
    rect.removeFromBottom(30);
    
    for (int i = 2; i >= 0; i--)
    {
        filterGainSlider[i].setBounds(rect.removeFromRight(getWidth()/5));
    }
    volumeSlider.setBounds(rect.removeFromLeft(getWidth()/5));
}

void AmpUI::sliderValueChanged (Slider* slider)
{
    auto sliderValue = slider->getValue();
    
    if (slider == &volumeSlider)
        ampAudio->volumeValue = sliderValue;
    
    else if (slider == &filterGainSlider[0])
        ampAudio->lowShelfGain = sliderValue;
    
    else if (slider == &filterGainSlider[1])
        ampAudio->midsPeakGain = sliderValue;
    
    else if (slider == &filterGainSlider[2])
        ampAudio->highShelfGain = sliderValue;
}
