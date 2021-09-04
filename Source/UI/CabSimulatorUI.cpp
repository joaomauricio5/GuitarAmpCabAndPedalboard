//  CabSimulator.cpp
//  AudioDeviceManagerTutorial - App
//
//  Created by João Mauricio UWE ID 18030724 on 17/01/2021.
//  Copyright © 2021 JUCE. All rights reserved.
//

#include "CabSimulatorUI.h"

CabSimulatorUI::CabSimulatorUI()
{
    addAndMakeVisible (cabSelector);
    cabSelector.addListener(this);
    
    StringArray cabsNamesList ("Cabinet 1", "Cabinet 2", "Cabinet 3", "Cabinet 4");
    cabSelector.addItemList(cabsNamesList, 1);
    cabSelector.setSelectedId(1, NotificationType::sendNotification);
    cabSelector.setJustificationType(Justification::Flags::centred);
}

void CabSimulatorUI::setCabSimulatorToControl (CabSimulatorAudio* cabSimulator)
{
    cabSimulatorAudio = cabSimulator;
}

void CabSimulatorUI::resized()
{
    cabSelector.setBounds(getLocalBounds());
}

void CabSimulatorUI::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    auto selectedId = comboBoxThatHasChanged->getSelectedId();
    cabSimulatorAudio->setImpulseResponse(selectedId - 1);
}

