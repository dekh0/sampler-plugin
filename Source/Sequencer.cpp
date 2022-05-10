#include "Sequencer.h"
#include <algorithm>
#include "TrigButtons.h"

bool Sequencer::tick()
{
    currentPosition++;
    if(currentPosition >= sequenceLeght)
        currentPosition = 0;
    if (triggers[currentPosition])
        return true;
    else
        return false;
}

void Sequencer::setTriggers(std::array<bool, 32> newTriggers)
{
    triggers = newTriggers;
}

