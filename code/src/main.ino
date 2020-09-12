// //sudo chmod a+rw /dev/ttyUSB0
#include "presure.h"
#include "water-pump.h"
#include "constants.h"
#include "systemEums.h"
#include "statusPanel.h"

float targetPresure;
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

        // activate redering mode
        statusPanel.setState(SystemEnums::SYSTEM_STATE_RENDERING);

        targetPresure = Serial.parseFloat();
        printMessage("target presure", targetPresure, "kPa");
        float normalizedPresure[2];
        normalizedPresure[0] = targetPresure - GlobalConstants ::NORM_PRESURE;
        normalizedPresure[1] = targetPresure + GlobalConstants ::NORM_PRESURE;
        while (presureSensor.getCurrentPresureInPascal() < normalizedPresure[0] || presureSensor.getCurrentPresureInPascal() > normalizedPresure[1])
        {
            if (presureSensor.getCurrentPresureInPascal() < normalizedPresure[0])
            {
                printMessage("presure", presureSensor.getCurrentPresureInPascal(), "kPa");
                waterPump.leftSpin();
            }
            else
            {
                printMessage("presure", presureSensor.getCurrentPresureInPascal(), "kPa");
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
        printMessage("redering completed !! presure", presureSensor.getCurrentPresureInPascal(), "kPa");
    }
}
