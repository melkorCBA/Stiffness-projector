#include "water-pump.h"
#include "constants.h"
#include "Arduino.h"

WaterPump ::WaterPump()
{
    pin1 = GlobalConstants::LN298_PIN_1;
    pin2 = GlobalConstants ::LN298_PIN_2;
    speedPin = GlobalConstants::LN298_PMW_PIN;
    speed = GlobalConstants::MOTOR_SPEED;
}

void WaterPump ::leftSpin()
{
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    analogWrite(speedPin, speed);
}

void WaterPump ::rightSpin()
{

    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(speedPin, speed);
}
void WaterPump ::stopMotor()
{
    {

        digitalWrite(pin2, LOW);
        digitalWrite(pin1, LOW);
        analogWrite(speedPin, 0);
    }
}