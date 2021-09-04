//
//  LevelMeterUI.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//

#pragma once
#include "JuceHeader.h"

/**Class copied and extended from AudioDeviceSelectorComponent::SimpleDeviceManagerInputLevelMeter to also be able to display output levels from the AudioDeviceManager */

class LevelMeter  : public Component,
public Timer
{
public:
    
    enum MeterOutputOrInput
    {
        Input,
        Output
    };
    /**LevelMeter constructor
     @param m reference to AudioDeviceManager to use for metering
     @param outputOrInput will this meter display the AudioDeviceManager input or output*/
    LevelMeter (AudioDeviceManager& m, MeterOutputOrInput outputOrInput);
    
private:
    /** Inherited from Timer and called every 20ms to display the current level, as set in the LevelMeter constructor */
    void timerCallback() override;
    
    /** Used to paint the level meter */
    void paint (Graphics& g) override;
    
    
    AudioDeviceManager& manager;
    AudioDeviceManager::LevelMeter::Ptr levelGetter;
    float level = 0;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelMeter)
};
