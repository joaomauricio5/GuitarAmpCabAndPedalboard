#include "MainComponent.h"

MainComponent::MainComponent(Audio& a) :    audio(a),
                                            audioSetupComp (audio.deviceManager,
                                                          0,     // minimum input channels
                                                          256,   // maximum input channels
                                                          0,     // minimum output channels
                                                          256,   // maximum output channels
                                                          false, // ability to select midi inputs
                                                          false, // ability to select midi output device
                                                          false, // treat channels as stereo pairs
                                                          false) // hide advanced options
                                            , inputLevelMeter(audio.deviceManager, LevelMeter::MeterOutputOrInput::Input),
                                              outputLevelMeter(audio.deviceManager, LevelMeter::MeterOutputOrInput::Output)

{
    addAndMakeVisible (ampUI);
    addAndMakeVisible(cabSimulatorUI);
    addAndMakeVisible (audioSetupComp);
    addAndMakeVisible(outputLevelMeter);
    addAndMakeVisible(inputLevelMeter);
    
    addAndMakeVisible (audioDeviceInfoDisplay);
    audioDeviceInfoDisplay.setDeviceManager(&audio.deviceManager);
    audioDeviceInfoDisplay.dumpDeviceInfo();
    
    addAndMakeVisible(chorusUI);
    addAndMakeVisible(phaserUI);
    addAndMakeVisible(reverbUI);
    addAndMakeVisible(overdriveDistortionUI);
    addAndMakeVisible(fuzzDistortionUI);
    addAndMakeVisible(noiseGateUI);
    addAndMakeVisible(delayUI);
    
    for (int i = 0; i < NumberOfPedals; i++)
    {
        addAndMakeVisible(pedalUI[i]);
        addAndMakeVisible(pedalSelector[i]);
        addAndMakeVisible(blankPedalUI[i]);
    }
    
    StringArray pedalsNamesList ("No Pedal", "Chorus", "Reverb", "Overdrive", "Noise Gate", "Delay", "Fuzz", "Phaser");
    for (int i = 0; i < NumberOfPedals; i++)
    {
        pedalSelector[i].addItemList(pedalsNamesList, 1);
        pedalSelector[i].addListener(this);
        pedalSelector[i].setJustificationType(Justification::centred);
    }

    // Setting the default pedalUIs
    pedalSelector[0].setSelectedId(5, sendNotification);
    pedalSelector[1].setSelectedId(4, sendNotification);
    pedalSelector[2].setSelectedId(2, sendNotification);
    pedalSelector[3].setSelectedId(3, sendNotification);
    
    pedalUI[0] = &noiseGateUI;
    pedalUI[1] = &overdriveDistortionUI;
    pedalUI[2] = &chorusUI;
    pedalUI[3] = &reverbUI;
    //
    
    reverbUI.setReverbToControl(audio.getReverbAudio());
    chorusUI.setChorusToControl(audio.getChorusAudio());
    phaserUI.setPhaserToControl(audio.getPhaserAudio());
    overdriveDistortionUI.setDistortionToControl(audio.getOverdriveDistortionAudio());
    fuzzDistortionUI.setDistortionToControl(audio.getFuzzDistortionAudio());
    noiseGateUI.setNoiseGateToControl(audio.getNoiseGate());
    ampUI.setAmpToControl(audio.getAmp());
    cabSimulatorUI.setCabSimulatorToControl(audio.getCabSimulator());
    delayUI.setDelayToControl(audio.getDelay());
    
    audio.deviceManager.addChangeListener (this);
    
    chorusUI.pedalToggle.addListener(this);
    phaserUI.pedalToggle.addListener(this);
    reverbUI.pedalToggle.addListener(this);
    overdriveDistortionUI.pedalToggle.addListener(this);
    fuzzDistortionUI.pedalToggle.addListener(this);
    noiseGateUI.pedalToggle.addListener(this);
    delayUI.pedalToggle.addListener(this);

    setSize (1500, 1000);
}

MainComponent::~MainComponent()
{
    audio.deviceManager.removeChangeListener (this);
}

void MainComponent::paint (Graphics& g)
{
    g.setColour (Colours::grey);
    g.fillRect(audioSetupComp.getBounds());
    g.fillRect(audioDeviceInfoDisplay.getBounds());
}

void MainComponent::resized()
{
    auto fullWindowRect = getLocalBounds();
    
    audioSetupComp.setItemHeight(getHeight()*0.02);
    auto audioDeviceSetupAndInfoRect = fullWindowRect.removeFromTop(audioSetupComp.getHeight());
    audioSetupComp.setBounds(audioDeviceSetupAndInfoRect.removeFromLeft(proportionOfWidth(0.6f)));
    audioDeviceInfoDisplay.setBounds(audioDeviceSetupAndInfoRect);
    
    
    auto inputMeterRect = fullWindowRect.removeFromTop(proportionOfHeight(0.03));
    inputMeterRect.reduce(450, 5);
    inputLevelMeter.setBounds(inputMeterRect);
    
    auto outputMeterRect = fullWindowRect.removeFromBottom(proportionOfHeight(0.05));
    outputMeterRect.reduce(450, 12);
    outputLevelMeter.setBounds(outputMeterRect);
    
    auto ampAndCabRect = fullWindowRect.removeFromBottom(proportionOfHeight(0.25));
    ampAndCabRect.removeFromRight(100);
    ampAndCabRect.removeFromLeft(100);
    cabSimulatorUI.setBounds(ampAndCabRect.removeFromBottom(proportionOfHeight(0.06)));
    ampUI.setBounds(ampAndCabRect);
    
    
    auto pedalsRect = fullWindowRect;
    pedalsRect.reduce(150, 0);

    Rectangle<int> individualPedalRect[4];
    for (int i = 0; i < NumberOfPedals; i++)
    {
        individualPedalRect[i] = pedalsRect.removeFromLeft(pedalsRect.getWidth()/ (4 - i));
        individualPedalRect[i].reduce(25, 10);
        pedalSelector[i].setBounds(individualPedalRect[i].removeFromTop(proportionOfHeight(0.05)));
        pedalUI[i]->setBounds(individualPedalRect[i]);
    }
}

void MainComponent::changeListenerCallback (ChangeBroadcaster*)
{
    audioDeviceInfoDisplay.dumpDeviceInfo();
    triggerAsyncUpdate();  // this is used to work around the fact that AudioDeviceSelectorComponent sometimes increases its size automatically when changing settings and ruins the layout
}

void MainComponent::handleAsyncUpdate() //this is used to work around the fact that AudioDeviceSelectorComponent sometimes increases its size automatically when changing settings and ruins the layout
{
    resized();
}

void MainComponent::buttonClicked (Button* toggle)
{
    if (toggle == &pedalUI[0]->pedalToggle)
        audio.isPedalToggleOn[0] = pedalUI[0]->pedalToggle.getToggleState();
    
    else if (toggle == &pedalUI[1]->pedalToggle)
        audio.isPedalToggleOn[1] = pedalUI[1]->pedalToggle.getToggleState();
    
    else if (toggle == &pedalUI[2]->pedalToggle)
        audio.isPedalToggleOn[2] = pedalUI[2]->pedalToggle.getToggleState();
    
    else if (toggle == &pedalUI[3]->pedalToggle)
        audio.isPedalToggleOn[3] = pedalUI[3]->pedalToggle.getToggleState();
}


void MainComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    int comboBoxIndex;
    
    for (int i = 0; i < NumberOfPedals; i++)
    {
        if (comboBoxThatHasChanged == &pedalSelector[i])
            comboBoxIndex = i;
    }
    
    int optionSelected = comboBoxThatHasChanged->getSelectedId();
    int pedalIndex = comboBoxIndex;
    
    makeAllComboBoxOptionsEnabled();
    makeAllOptionsSelectedUnavailableInAllComboBoxes();
    
    if (optionSelected == 1)
    {
        displayAndUseDifferentPedalUI(pedalIndex, blankPedalUI[pedalIndex]);
    }
    
    else if (optionSelected == 2)
    {
        displayAndUseDifferentPedalUI(pedalIndex, chorusUI);
        audio.setPedal(pedalIndex, Audio::PedalsAvailable::Chorus);
    }
    
    else if (optionSelected == 3)
    {
        displayAndUseDifferentPedalUI(pedalIndex, reverbUI);
        audio.setPedal(pedalIndex, Audio::PedalsAvailable::Reverb);
    }
    
    else if (optionSelected == 4)
    {
        displayAndUseDifferentPedalUI(pedalIndex, overdriveDistortionUI);
        audio.setPedal(pedalIndex, Audio::PedalsAvailable::Overdrive);
    }
    
    else if (optionSelected == 5)
    {
        displayAndUseDifferentPedalUI(pedalIndex, noiseGateUI);
        audio.setPedal(pedalIndex, Audio::PedalsAvailable::NoiseGate);
    }
    
    else if (optionSelected == 6)
    {
        displayAndUseDifferentPedalUI(pedalIndex, delayUI);
        audio.setPedal(pedalIndex, Audio::PedalsAvailable::Delay);
    }
    
    else if (optionSelected == 7)
    {
        displayAndUseDifferentPedalUI(pedalIndex, fuzzDistortionUI);
        audio.setPedal(pedalIndex, Audio::PedalsAvailable::Fuzz);
    }
    
    else if (optionSelected == 8)
    {
        displayAndUseDifferentPedalUI(pedalIndex, phaserUI);
        audio.setPedal(pedalIndex, Audio::PedalsAvailable::Phaser);
    }
}

void MainComponent::makeAllOptionsSelectedUnavailableInAllComboBoxes() // Sets all pedal types that are already selected unavailable to choose in all comboBoxes. Restricts the user to not being able to have 2 or more pedals of the same type
{
    for (int i = 0; i < NumberOfPedals; i++)
        {
            int currentSelectedID = pedalSelector[i].getSelectedId();
            
            if (currentSelectedID != 1) 
            {
                for (int z = 0; z < NumberOfPedals; z ++)
                {
                    pedalSelector[z].setItemEnabled(currentSelectedID, false);
                }
            }
        }
}

void MainComponent::makeAllComboBoxOptionsEnabled() // Enables all comboBox options in every comboBox
{
    for (int i = 0; i < NumberOfPedals; i++)
    {
        for (int z = 1; z <= pedalSelector[i].getNumItems(); z++)
        {
            pedalSelector[i].setItemEnabled(z, true);
        }
    }
}
