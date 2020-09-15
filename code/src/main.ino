// //sudo chmod a+rw /dev/ttyUSB0
#include "presure.h"
#include "water-pump.h"
#include "constants.h"
#include "systemEums.h"
#include "statusPanel.h"

float targetPresure;
float serialRead;
void printMessage(String preMessage, float value, String postMessage);
WaterPump waterPump;
PresureSensor presureSensor;
StatusPanel statusPanel;

void setup()
{

    Serial.begin(9600);
    pinMode(GlobalConstants::RELAY_PIN_1, OUTPUT);
    pinMode(GlobalConstants::RELAY_PIN_1, OUTPUT);
    pinMode(GlobalConstants::LN298_PMW_PIN, OUTPUT);

    waterPump = WaterPump();
    presureSensor = PresureSensor();
    statusPanel = StatusPanel();

    statusPanel.setStatus(SystemEnums::SYSTEM_ON);
}

void loop()
{
    statusPanel.setState(SystemEnums::SYSTEM_STATE_IDEAL);
    if (Serial.available())
    {

        serialRead = Serial.parseFloat();
        if (serialRead != 0.0)
        {
            targetPresure = serialRead;
            printMessage("target presure", targetPresure, "kPa");
        }
    }
    if (targetPresure != 0.0)
    {
        printMessage("system presure", presureSensor.getCurrentPresureInPascal(), "kPa");
        renderPresure();
    }
}

void renderPresure()

{

    float normalizedPresure[2];
    normalizedPresure[0] = targetPresure - GlobalConstants ::NORM_PRESURE;
    normalizedPresure[1] = targetPresure + GlobalConstants ::NORM_PRESURE;
    while (presureSensor.getCurrentPresureInPascal() < normalizedPresure[0] || presureSensor.getCurrentPresureInPascal() > normalizedPresure[1])
    {
        // activate redering mode
        statusPanel.setState(SystemEnums::SYSTEM_STATE_RENDERING);
        printMessage("---------------------------------------------------", 0, "");
        printMessage("Redering started !! [target presure]", targetPresure, "kPa");

        if (presureSensor.getCurrentPresureInPascal() < normalizedPresure[0])
        {
            printMessage("system presure", presureSensor.getCurrentPresureInPascal(), "kPa");
            waterPump.leftSpin();
        }
        else
        {
            printMessage("system presure", presureSensor.getCurrentPresureInPascal(), "kPa");
            waterPump.rightSpin();
        }
        if (Serial.available())
        {
            waterPump.stopMotor();
            break;
        }
    }

    // change state to ideal model
    statusPanel.setState(SystemEnums::SYSTEM_STATE_IDEAL);
    waterPump.stopMotor();

    printMessage("redering completed !! at presure", presureSensor.getCurrentPresureInPascal(), "kPa");
    printMessage("---------------------------------------------------", 0, "");
}
