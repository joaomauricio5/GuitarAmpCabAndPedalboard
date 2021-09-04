#pragma once

#include <JuceHeader.h>

#include "CabSimulatorUI.h"
#include "AmpUI.h"
#include "LevelMeterUI.h"

#include "PedalsUI/ReverbUI.h"
#include "PedalsUI/ChorusUI.h"
#include "PedalsUI/PhaserUI.h"
#include "PedalsUI/NoiseGateUI.h"
#include "PedalsUI/Pedal.h"
#include "PedalsUI/OverdriveUI.h"
#include "PedalsUI/FuzzUI.h"
#include "PedalsUI/DelayUI.h"
#include "PedalsUI/BlankPedalUI.cpp"
#include "AudioDeviceInfoDisplay.h"

#include "../Audio/Audio.h"

/** Brings together all of the components of the GUI.*/

class MainComponent  : public Component,
                       public ChangeListener,
                       public Button::Listener,
                       public ComboBox::Listener,
                       public AsyncUpdater
{
public:

    /** MainComponent  constructor
     @param a reference to Audio object*/
    MainComponent(Audio& a);
    /** MainComponent  destructor */
    ~MainComponent() override;
  
    /**Number of pedal slots to display*/
    enum
    {
        NumberOfPedals = 4
    };
    
    /**Paints the main UI*/
    void paint (Graphics& g) override;
    
    /**Called when the size of the window changes. Used to set the bounds of all components in MainComponent*/
    void resized() override;
    
    /**Called when there is a change in the current AudioDeviceManager*/
    void changeListenerCallback (ChangeBroadcaster*) override;
    
    /**Used to work around the fact that the size of an AudioDeviceSelectorComponent changes its own size depending on some settings chosen*/
    virtual void handleAsyncUpdate() override;
    
    /**Listens to the pedal toggles to turn their audio processing on/off*/
    void buttonClicked (Button*) override;
    
    /**Listens to changes in the pedal slots combo boxes to set pedalUI and pedalAudio to specific pedal types*/
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    
private:
    Audio& audio;
    
    Pedal* pedalUI[NumberOfPedals] = {nullptr};
    ComboBox pedalSelector[NumberOfPedals];
    
    AudioDeviceSelectorComponent audioSetupComp;
    LevelMeter inputLevelMeter;
    LevelMeter outputLevelMeter;
    AudioDeviceInfoDisplay audioDeviceInfoDisplay;
    AmpUI ampUI;
    CabSimulatorUI cabSimulatorUI;
    
    OverdriveUI overdriveDistortionUI;
    FuzzUI fuzzDistortionUI;
    ReverbUI reverbUI;
    ChorusUI chorusUI;
    PhaserUI phaserUI;
    NoiseGateUI noiseGateUI;
    DelayUI delayUI;
    BlankPedalUI blankPedalUI[NumberOfPedals];
    
    /**Template class that sets a pedal slot to display a specific pedalUI
     @param pedalIndexToChange index of the pedal slot to change
     @param pedalUItoChangeTo type of pedalUI for pedalUI[pedalIndexToChange] to use*/
    template <class PedalType>
    void displayAndUseDifferentPedalUI (int pedalIndexToChange,  PedalType& pedalUItoChangeTo)
    {
        pedalUI[pedalIndexToChange]->pedalToggle.setToggleState(false, sendNotification);
        pedalUI[pedalIndexToChange]->setVisible(false);
        pedalUI[pedalIndexToChange] = &pedalUItoChangeTo;
        pedalUI[pedalIndexToChange]->setVisible(true);
        pedalUI[pedalIndexToChange]->pedalToggle.setToggleState(true, sendNotification);
        resized();
    }
    /**Sets all pedal types that are already selected unavailable to choose in all comboBoxes. Restricts the user to not being able to have 2 or more pedals of the same type*/
    void makeAllOptionsSelectedUnavailableInAllComboBoxes();
    
    /**Enables all comboBox options in every comboBox*/
    void makeAllComboBoxOptionsEnabled();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
