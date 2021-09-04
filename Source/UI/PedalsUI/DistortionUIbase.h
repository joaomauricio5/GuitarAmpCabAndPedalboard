//
//  DistortionUIbase.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//

#pragma once


#include "JuceHeader.h"
#include "Pedal.h"

/** Base class for the UI of the two distortion pedals (Overdrive and Fuzz), which will both have two similar sliders(preGain and outputGain */
class DistortionUIbase : public Pedal
{
public:
    /** DistortionUIbase  constructor */
    DistortionUIbase();
    
private:
/** Inherited from component to paint the pedal */
    void resized() override;

    /** Callback for the slider changes in the classes that inherit from DistortionUIbase */
    virtual void sliderValueChanged (Slider* slider) override = 0;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionUIbase)
};
