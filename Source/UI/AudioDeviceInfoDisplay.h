//
//  AudioDeviceInfoDisplay.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//

#pragma once
#include "JuceHeader.h"

/** Class adapted from JUCE's tutorial "Tutorial: The AudioDeviceManagerClass" to display the current settings of the AudioDeviceManager it mirrors as well as the current cpu usage */

class AudioDeviceInfoDisplay :  public Component,
                                private Timer
{
public:
    /** AudioDeviceInfoDisplay  constructor */
    AudioDeviceInfoDisplay();
    /** AudioDeviceInfoDisplay  destructor */
    ~AudioDeviceInfoDisplay() override;

    /** Sets the AudioDeviceManager object that the AudioDeviceInfoDisplay will mirror
    @param deviceManagerToDisplay pointer to the ChorusAudio object to display*/
    void setDeviceManager(AudioDeviceManager* deviceManagerToDisplay);
    
    /** Outputs the AudioDeviceManager's current settings as logMessages. It should be called in a changeListenerCallback*/
    void dumpDeviceInfo();

private:
    
    /** Inherited from Component to layout all of the AudioDeviceInfoDisplay's children*/
    void resized() override;
    
    static String getListOfActiveBits (const BigInteger& b);
    
    void logMessage (const String& m);
    
    /** Inherited from Timer and called every 50ms to display the cpu usage, as set in the AudioDeviceInfoDisplay constructor */
    void timerCallback() override;

    //==========================================================================
 
   Label cpuUsageLabel;
   Label cpuUsageText;
   TextEditor diagnosticsBox;
    
    std::atomic<AudioDeviceManager*> deviceManagerAtomic;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioDeviceInfoDisplay)
};
