//
//  AmpUI.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//

#pragma once
#include "JuceHeader.h"
#include "../Audio/AmpAudio.h"

/** Class for the UI of the Amp, which changes the parameters of a AmpAudio object that it's assigned to control
@see setAmpToControl */

class AmpUI : public Component,
              public Slider::Listener
{
public:
    
    /** AmpUI  constructor */
    AmpUI();
    
    /** Sets the AmpAudio object that the AmpUI will control
    @param amp pointer to the AmpAudio object to control*/
    void setAmpToControl (AmpAudio* amp);
    
private:
    
    /** Inherited from Component to paint the pedal */
    void paint (Graphics& g) override;
    
    /** Inherited from Component to layout all of the AmpUI's children*/
    void resized() override;
    
    /** Callback for the slider changes in the AmpUI */
    virtual void sliderValueChanged (Slider* slider) override;

    AmpAudio* ampAudio = nullptr;

    float lastSampleRate;
    
    Slider filterGainSlider[3];
    Label filterGainLabel[3];

    Slider volumeSlider {Slider::SliderStyle::Rotary, Slider::TextEntryBoxPosition::TextBoxBelow};
    Label volumeLabel {"volumeLabel", "Volume"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpUI)
};
