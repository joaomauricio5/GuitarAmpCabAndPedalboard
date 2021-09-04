//
//  ChorusUI.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//

#pragma once

#include "JuceHeader.h"
#include "../Source/Audio/PedalsAudio/ChorusAudio.h"
#include "Pedal.h"

/** Class for the UI of the chorus pedal, which changes the parameters of a ChorusAudio object that it's assigned to control
 @see setChorusToControl */
class ChorusUI : public Pedal
{
public:
    /** ChorusUI  constructor */
    ChorusUI();
    
    /** Sets the ChorusAudio object that the ChorusUI will control
     @param chorus pointer to the ChorusAudio object to control*/
    void setChorusToControl (ChorusAudio* chorus);
    
private:
    
    /** Inherited from component to paint the pedal */
    void paint (Graphics& g) override;
    
    /** Callback for the slider changes in the ChorusUI */
    virtual void sliderValueChanged (Slider* sliderReceived) override;
    
    ChorusAudio* chorusAudio = nullptr;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusUI)
};
