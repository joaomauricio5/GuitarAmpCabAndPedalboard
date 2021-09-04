//
//  PhaserUI.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//
#pragma once

#include "JuceHeader.h"
#include "../Source/Audio/PedalsAudio/PhaserAudio.h"
#include "Pedal.h"

/** Class for the UI of the phaser pedal, which changes the parameters of a PhaserAudio object that it's assigned to control */
class PhaserUI : public Pedal
{
public:
    /** PhaserUI  constructor */
    PhaserUI();
    /** Sets the PhaserAudio object that the PhaserUI will control
     @param phaser pointer to the PhaserAudio object to control*/
    void setPhaserToControl (PhaserAudio* phaser);
    
private:
    /** Inherited from Component to paint the pedal */
    void paint (Graphics& g) override;
    
    /** Callback for the slider changes in the PhaserUI */
    virtual void sliderValueChanged (Slider* sliderReceived) override;
    
    PhaserAudio* phaserAudio = nullptr;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaserUI)
};
