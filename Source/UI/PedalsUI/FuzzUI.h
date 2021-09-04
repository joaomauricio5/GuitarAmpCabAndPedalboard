//
//  FuzzUI.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//
#pragma once

#include "JuceHeader.h"
#include "DistortionUIbase.h"
#include "../Source/Audio/PedalsAudio/FuzzAudio.h"

/** Class for the UI of the fuzz pedal, which changes the parameters of a FuzzAudio object that it's assigned to control */

class FuzzUI : public DistortionUIbase
{
public:
    /** FuzzUI  constructor */
    FuzzUI();
    /** Sets the FuzzAudio object that the FuzzUI will control
     @param fuzz pointer to the FuzzAudio object to control*/
    void setDistortionToControl (FuzzAudio* fuzz);
    
private:
    /** Inherited from component to paint the pedal */
    void paint (Graphics& g) override;
    /** Callback for the slider changes in the FuzzUI */
    void sliderValueChanged (Slider* sliderReceived) override;
    
    FuzzAudio* fuzzAudio = nullptr;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FuzzUI)
};
