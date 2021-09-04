//
//  OutputLimiter.cpp
//  SDAassignment - App
//
//  Created by João Mauricio UWE ID 18030724 on 07/02/2021.
//

#pragma once

#include "JuceHeader.h"

/** Simple hard limiter that inherits from dsp::WaveShaper to restrict the samples that it outputs to an amplitude of -1.0 to 1.0 */

struct OutputLimiter : public dsp::WaveShaper<float>

{
    /** ChorusAudio constructor. Sets the transfer function of the waveshaper to be that of a hard limiter*/
    OutputLimiter()
    {
        functionToUse = [] (float x)
        {
             return jlimit (float (-1), float (1), x);  //     HARD LIMITER
        };
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputLimiter)
};
