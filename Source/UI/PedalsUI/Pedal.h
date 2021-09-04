//
//  Pedal.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//
#pragma once

#include "JuceHeader.h"
/** Base class for the UI of all of the pedals. Has a variable number of sliders (which the class inheriting from Pedal will determine) and a toggle that controls an assigned audio pedal class  */

class Pedal :    public Component,
                 public Slider::Listener
{
public:
    /** Pedal constructor, where the number of sliders needed for the pedal UI is requested
     @param numOfSliders number of sliders that the class inheriting from Pedal will need*/
    Pedal(int numOfSliders);
    
    ToggleButton pedalToggle;
    
    /** Array for all of the sliders requested in Pedal's constructor
     @see Pedal(int numOfSliders) */
    OwnedArray<Slider> slider;
    
    OwnedArray<Label> sliderLabel;
    
private:
    /** Resized function inherited from component */
    void resized() override;
    
    /** Paint function inherited from component */
    virtual void paint (Graphics& g) override;
    
    /** Callback for the slider changes in the pedal UI */
    virtual void sliderValueChanged (Slider* sliderReceived) override;
    
    int NumberOfSliders;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pedal)
};
