//  AudioDeviceInfoDisplay.cpp
//  AudioDeviceManagerTutorial - App
//
//  Created by João Mauricio UWE ID 18030724 on 16/01/2021.
//  Copyright © 2021 JUCE. All rights reserved.
//

#include "AudioDeviceInfoDisplay.h"


/* Class adapted from JUCE's tutorial "Tutorial: The AudioDeviceManagerClass" to display the current settings of the AudioDeviceManager it mirrors as well as the current cpu usage */

AudioDeviceInfoDisplay::AudioDeviceInfoDisplay()
{
    addAndMakeVisible (diagnosticsBox);
    
    diagnosticsBox.setMultiLine (true);
    diagnosticsBox.setReturnKeyStartsNewLine (true);
    diagnosticsBox.setReadOnly (true);
    diagnosticsBox.setScrollbarsShown (true);
    diagnosticsBox.setCaretVisible (false);
    diagnosticsBox.setPopupMenuEnabled (true);
    diagnosticsBox.setColour (TextEditor::backgroundColourId, Colour (0x32ffffff));
    diagnosticsBox.setColour (TextEditor::outlineColourId,    Colour (0x1c000000));
    diagnosticsBox.setColour (TextEditor::shadowColourId,     Colour (0x16000000));
    
    cpuUsageLabel.setText ("CPU Usage", dontSendNotification);
    cpuUsageText.setJustificationType (Justification::right);
    addAndMakeVisible (&cpuUsageLabel);
    addAndMakeVisible (&cpuUsageText);
    
    startTimer (50);
}

AudioDeviceInfoDisplay::~AudioDeviceInfoDisplay()
{
    
}



void AudioDeviceInfoDisplay::setDeviceManager(AudioDeviceManager *deviceManagerToControl)
{
    deviceManagerAtomic = deviceManagerToControl;
}

void AudioDeviceInfoDisplay::dumpDeviceInfo()
{
    auto deviceManager = deviceManagerAtomic.load();
    logMessage ("--------------------------------------");
    logMessage ("Current audio device type: " + (deviceManager->getCurrentDeviceTypeObject() != nullptr
                                                 ? deviceManager->getCurrentDeviceTypeObject()->getTypeName()
                                                 : "<none>"));
    
    if (auto* device = deviceManager->getCurrentAudioDevice())
    {
        logMessage ("Current audio device: "   + device->getName().quoted());
        logMessage ("Sample rate: "    + String (device->getCurrentSampleRate()) + " Hz");
        logMessage ("Block size: "     + String (device->getCurrentBufferSizeSamples()) + " samples");
        logMessage ("Bit depth: "      + String (device->getCurrentBitDepth()));
        logMessage ("Input channel names: "    + device->getInputChannelNames().joinIntoString (", "));
        logMessage ("Active input channels: "  + getListOfActiveBits (device->getActiveInputChannels()));
        logMessage ("Output channel names: "   + device->getOutputChannelNames().joinIntoString (", "));
        logMessage ("Active output channels: " + getListOfActiveBits (device->getActiveOutputChannels()));
    }
    else
    {
        logMessage ("No audio device open");
    }
}


void AudioDeviceInfoDisplay::resized()
{
    auto rect = getLocalBounds();
    
    auto topLine (rect.removeFromTop (20));
    cpuUsageLabel.setBounds (topLine.removeFromLeft (topLine.getWidth() / 2));
    cpuUsageText .setBounds (topLine);
    rect.removeFromTop (20);
    
    diagnosticsBox.setBounds (rect);
}

String AudioDeviceInfoDisplay::getListOfActiveBits (const BigInteger& b)
{
    StringArray bits;
    
    for (auto i = 0; i <= b.getHighestBit(); ++i)
        if (b[i])
            bits.add (String (i));
    
    return bits.joinIntoString (", ");
}

//! [timerCallback]
void AudioDeviceInfoDisplay::timerCallback()
{
    auto deviceManager = deviceManagerAtomic.load();
    auto cpu = deviceManager->getCpuUsage() * 100;
    cpuUsageText.setText (String (cpu, 6) + " %", dontSendNotification);
}

void AudioDeviceInfoDisplay::logMessage (const String& m)
{
    diagnosticsBox.moveCaretToEnd();
    diagnosticsBox.insertTextAtCaret (m + newLine);
}

