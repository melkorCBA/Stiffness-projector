#include "statusPanel.h"
#include "Arduino.h"
#include "constants.h"
#include "systemEums.h"

StatusPanel::StatusPanel()
{
    status = false;
    state = 0;
    stateIdealPin = GlobalConstants::STATE_IDEAL_PIN;
    stateRenderingPin = GlobalConstants::STATE_RENDERING_PIN;
    statusPin = GlobalConstants::STATUS_PIN;
}

void StatusPanel::setStatus(bool state)
{
    if (state)
    {

        digitalWrite(statusPin, HIGH);
    }
    else
    {
        digitalWrite(statusPin, LOW);
    }
    this->status = status;
}

void StatusPanel::setState(int state)
{

    if (state == SystemEnums::SYSTEM_STATE_IDEAL)
    {
        digitalWrite(stateIdealPin, HIGH);
        digitalWrite(stateRenderingPin, LOW);
    }

    if (state == SystemEnums::SYSTEM_STATE_RENDERING)
    {

        digitalWrite(stateRenderingPin, HIGH);
        digitalWrite(stateIdealPin, LOW);
    }

    if (state == SystemEnums::SYSTEM_STATE_STANDBY)
    {
        digitalWrite(stateRenderingPin, LOW);
        digitalWrite(stateIdealPin, LOW);
    }
}

bool StatusPanel::getStatus()
{
    return this->status;
}

int StatusPanel::getState()
{
    return this->state;
}
