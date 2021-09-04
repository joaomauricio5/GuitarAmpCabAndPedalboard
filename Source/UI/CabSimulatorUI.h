//
//  CabSimulatorUI.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//

#pragma once
#include "JuceHeader.h"
#include "../Audio/CabSimulatorAudio.h"

/** Class for the UI of a cab simulator, which changes the impulse response that a CabSimulatorAudio object is using through a comboBox*/

class CabSimulatorUI : public Component,
                       public ComboBox::Listener
{
public:
    /** CabSimulatorUI  constructor */
    CabSimulatorUI();
    
    /** Sets the CabSimulatorAudio object that the CabSimulatorUI will control
    @param cabSimulator pointer to the CabSimulatorAudio object to control*/
    void setCabSimulatorToControl (CabSimulatorAudio* cabSimulator);
    
private:
    
    /** Inherited from component to paint the pedal */
    void resized() override;
    
    /** Callback for the comboBox changes in the CabSimulatorUI */
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    
    ComboBox cabSelector;
    
    CabSimulatorAudio* cabSimulatorAudio = nullptr;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CabSimulatorUI)
};
