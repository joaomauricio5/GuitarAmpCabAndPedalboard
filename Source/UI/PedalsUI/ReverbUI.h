//
//  ReverbUI.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//
#pragma once

#include "JuceHeader.h"
#include "../Source/Audio/PedalsAudio/ReverbAudio.h"
#include "Pedal.h"

/** Class for the UI of the reverb pedal, which changes the parameters of a ReverbAudio object that it's assigned to control */

class ReverbUI : public Pedal
{
public:
    /** ReverbUI  constructor */
    ReverbUI();
    
    /** Sets the ReverbAudio object that the ReverbUI will control
     @param reverb pointer to the ReverbAudio object to control*/
    void setReverbToControl (ReverbAudio* reverb);
    
private:
    
    /** Callback for the slider changes in the ReverbUI */
    virtual void sliderValueChanged (Slider* sliderReceived) override;
    
    ReverbAudio* reverbAudio = nullptr;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbUI)
};
