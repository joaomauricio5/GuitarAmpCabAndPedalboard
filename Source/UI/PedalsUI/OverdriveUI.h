//
//  OverdriveUI.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//
#pragma once


#include "JuceHeader.h"
#include "DistortionUIbase.h"
#include "../Source/Audio/PedalsAudio/OverdriveAudio.h"

/** Class for the UI of the overdrive pedal, which changes the parameters of a OverdriveAudio object that it's assigned to control */

class OverdriveUI : public DistortionUIbase

{
public:
    /** OverdriveUI constructor*/
    OverdriveUI();
    
    /** Sets the OverdriveAudio object that the OverdriveUI controls
     @param overdrive pointer to the OverdriveAudio object to control*/
    void setDistortionToControl (OverdriveAudio* overdrive);
    
private:
    /** Inherited from Component to paint the pedal */
    void paint (Graphics& g) override;
    /** Callback for the slider changes in the OverdriveUI */
    void sliderValueChanged (Slider* sliderReceived) override;
    
    OverdriveAudio* overdriveAudio = nullptr;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OverdriveUI)
};
