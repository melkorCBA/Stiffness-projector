#include "presure.h"
#include "constants.h"
#include "Arduino.h"

PresureSensor ::PresureSensor()
{
    inputPin = GlobalConstants::PRESURE_SENSOR_PIN;
}

float PresureSensor ::getCurrentPresureInPascal()
{
    int P = ((analogRead(inputPin) * 5.00 / 1024) - GlobalConstants ::OFFSET_PRESURE) * 400;
    return P;
}