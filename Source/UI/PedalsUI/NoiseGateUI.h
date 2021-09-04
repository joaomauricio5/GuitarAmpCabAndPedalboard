//
//  NoiseGateUI.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//

#pragma once

#include "JuceHeader.h"
#include "../Source/Audio/PedalsAudio/NoiseGateAudio.h"
#include "Pedal.h"

/** Class for the UI of the noise gate pedal, which changes the parameters of a NoiseGateAudio object that it's assigned to control */

class NoiseGateUI : public Pedal
{
public:
    /** DelayUI  constructor */
    NoiseGateUI();
    /** Sets the NoiseGateAudio object that the NoiseGateUI will control
     @param noiseGate pointer to the NoiseGateAudio object to control*/
    void setNoiseGateToControl (NoiseGateAudio* noiseGate);
    
private:
    
    /** Inherited from component to paint the pedal */
    void paint (Graphics& g) override;
    
    /** Callback for the slider changes in the NoiseGateUI */
    virtual void sliderValueChanged (Slider* sliderReceived) override;
    
    NoiseGateAudio* noiseGateAudio = nullptr;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseGateUI)
};
