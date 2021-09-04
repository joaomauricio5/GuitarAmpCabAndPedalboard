//
//  FuzzAudio.h
//  SDAassignment
//
//  Created by João Mauricio UWE ID 18030724 on 16/02/2021.
//

#pragma once
#include "DistortionAudioBase.h"

/** Class for the audio processing of the Fuzz pedal. Inherits from DistortionAudioBase and changes the transfer function that the waveshaper from DistortionAudioBase will use */
class FuzzAudio : public DistortionAudioBase
{
public:

    /** FuzzAudio constructor*/
    FuzzAudio();
    /** FuzzAudio destructor*/
    virtual ~FuzzAudio();
    
private:
    /**Sets the transfer function that the waveshaper from DistortionAudioBase will use*/
    void setTransferFunctionToUse() override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FuzzAudio)
};
