#pragma once

#include <JuceHeader.h>
//#include "TrigButtons.h"

//#include "PluginProcessor.h"

class Sequencer
{
public:
    
    bool tick(void);
    void setTriggers(std::array<bool, 32> triggers);
//    bool* getTriggers(void);
    
private:
    
    int sequenceLeght { 32 };
    
    std::array<bool, 32>  triggers
    {
        true, false, false, false,
        true, false, false, false,
        true, false, false, false,
        true, false, false, false,
        true, false, false, false,
        true, false, false, false,
        true, false, false, false,
        true, false, false, false
    };
    
    int currentPosition { -1 };
};



