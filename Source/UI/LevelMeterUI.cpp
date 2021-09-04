#include "LevelMeterUI.h"


/*Class copied and extended from AudioDeviceSelectorComponent::SimpleDeviceManagerInputLevelMeter to also be able to display output levels from the AudioDeviceManager */


LevelMeter::LevelMeter (AudioDeviceManager& m, MeterOutputOrInput outputOrInput )  : manager (m)
{
    startTimerHz (20);
    
    if (outputOrInput == MeterOutputOrInput::Input)
        levelGetter = manager.getInputLevelGetter();
    else if (outputOrInput == MeterOutputOrInput::Output)
        levelGetter = manager.getOutputLevelGetter();
}

void LevelMeter::timerCallback()
{
    if (isShowing())
    {
        auto newLevel = (float) levelGetter->getCurrentLevel();
        
        if (std::abs (level - newLevel) > 0.005f)
        {
            level = newLevel;
            repaint();
        }
    }
    else
    {
        level = 0;
    }
}

void LevelMeter::paint (Graphics& g)
{
    // (add a bit of a skew to make the level more obvious)
    getLookAndFeel().drawLevelMeter (g, getWidth(), getHeight(),
                                     (float) std::exp (std::log (level) / 3.0));
}


