//
//  DelayUI.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//

#pragma once

#include "JuceHeader.h"
#include "../Source/Audio/PedalsAudio/DelayAudio.h"
#include "Pedal.h"

/** Class for the UI of the delay pedal, which changes the parameters of a DelayAudio object that it's assigned to control */
class DelayUI : public Pedal

{
public:
    /** DelayUI  constructor */
    DelayUI();
    
    /** Sets the DelayAudio object that the DelayUI will control
     @param delay pointer to the DelayAudio object to control*/
    void setDelayToControl (DelayAudio* delay);
    
private:
    
    /** Inherited from Component to paint the pedal */
    void paint (Graphics& g) override;
    
    /** Callback for the slider changes in the DelayUI */
    virtual void sliderValueChanged (Slider* sliderReceived) override;
    
    DelayAudio* delayAudio = nullptr;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayUI)
};

