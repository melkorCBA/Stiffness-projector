#include "water-pump.h"
#include "constants.h"
#include "Arduino.h"

WaterPump ::WaterPump()
{
    pin1 = GlobalConstants::RELAY_PIN_1;
    pin2 = GlobalConstants ::RELAY_PIN_2;
}

void WaterPump ::leftSpin()
{
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
}

void WaterPump ::rightSpin()
{
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
}
void WaterPump ::stopMotor()
{
    {
        digitalWrite(pin2, LOW);
        digitalWrite(pin1, LOW);
    }
}