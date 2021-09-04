//
//  BlankPedalUI.cpp
//  SDAassignment - App
//
//  Created by João Mauricio UWE ID 18030724 on 08/02/2021.
//

#pragma once

#include "JuceHeader.h"
#include "Pedal.h"

/** Class for the UI of a blank pedal, for when the user decides not to choose a pedal in a pedal slot. */
class BlankPedalUI : public Pedal
{
public:
    /** BlankPedalUI  constructor */
    BlankPedalUI() : Pedal(0)
    {
        removeAllChildren();
    }
    
private:
    /** Inherited from component to paint the pedal */
    void paint (Graphics& g) override
    {
        g.setColour (Colours::darkgrey);
        g.fillAll();
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlankPedalUI)
};

