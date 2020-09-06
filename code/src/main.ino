// //sudo chmod a+rw /dev/ttyUSB0
// #include "projector.h"
#include "presure.h"
#include "water-pump.h"
#include "constants.h"

float targetPresure = GlobalConstants::MAT_A_BOUND_PRESURE;
void printMessage(String preMessage, float value, String postMessage);
WaterPump waterPump;
PresureSensor presureSensor;

void setup()
{

    Serial.begin(9600);
    pinMode(GlobalConstants::RELAY_PIN_1, OUTPUT);
    pinMode(GlobalConstants::RELAY_PIN_1, OUTPUT);

    waterPump = WaterPump();
    presureSensor = PresureSensor();
}

void loop()
{

    if (Serial.available())
    { //id data is available to read

        char val = Serial.read();

        if (val == 'A')
        {
            targetPresure = GlobalConstants::MAT_A_BOUND_PRESURE;
            printMessage("clicked", 0, "A");
            digitalWrite(13, HIGH);
        }
        if (val == 'B')
        {
            targetPresure = GlobalConstants::MAT_B_BOUND_PRESURE;
            printMessage("clicked", 0, "B");
            digitalWrite(13, LOW);
        }
        if (val == 'C')
        {
            targetPresure = GlobalConstants::MAT_C_BOUND_PRESURE;
            printMessage("clicked", 0, "C");
        }
        if (val == 'D')
        {
            targetPresure = GlobalConstants::MAT_D_BOUND_PRESURE;
            printMessage("clicked", 0, "D");
        }
    }
}