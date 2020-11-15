// //sudo chmod a+rw /dev/ttyUSB0
#include "presure.h"
#include "water-pump.h"
#include "constants.h"
#include "systemEums.h"
#include "statusPanel.h"

float targetPresure;
float serialRead;
void printMessage(String preMessage, float value, String postMessage);
void printMessage(String preMessage);
WaterPump waterPump;
PresureSensor presureSensor;
StatusPanel statusPanel;

void setup()
{

    Serial.begin(GlobalConstants::BAUD_RATE);
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

    // waterPump.leftSpin();
    // delay(3000);
    // waterPump.rightSpin();
    // delay(3000);
    // waterPump.stopMotor();
    // delay(3000);

    // digitalWrite(8, LOW);
    // digitalWrite(2, HIGH);
    // analogWrite(10, 70);
    // Serial.println("Spin 1");
    // delay(3000);

    // digitalWrite(8, LOW);
    // digitalWrite(2, LOW);
    // Serial.println("stop");
    // analogWrite(10, 0);
    // delay(3000);

    // digitalWrite(8, HIGH);
    // digitalWrite(2, LOW);
    // Serial.println("Spin 2");
    // analogWrite(10, 70);
    // delay(3000);
    // digitalWrite(8, LOW);
    // digitalWrite(2, LOW);
    // Serial.println("stop");
    // analogWrite(10, 0);
    // delay(3000);
    // // analogWrite(10, 70);
}

void renderPresure()

{

    float currentPresure = presureSensor.getCurrentPresureInPascal();
    if (isRenderNeeded(targetPresure, currentPresure))
    {
        // activate redering mode
        statusPanel.setState(SystemEnums::SYSTEM_STATE_RENDERING);
        printMessage("--------------------------------------------------------");
        printMessage("Rendering started !! [target presure]", targetPresure, "kPa");
        printMessage("--------------------------------------------------------");
        printMessage("Rendering !! [current presure]", currentPresure, "kPa");

        while (isRenderNeeded(targetPresure, currentPresure))
        {

            if (currentPresure < getLowerBoundPresure(targetPresure, currentPresure))
            {
                waterPump.leftSpin();
                // waterPump.rightSpin();
                delay(2000);
            }
            else
            {
                waterPump.rightSpin();
                // waterPump.leftSpin();
                delay(2000);
            }
            if (Serial.available())
            {
                waterPump.stopMotor();
                break;
            }
            // update current presure
            currentPresure = presureSensor.getCurrentPresureInPascal();
            printMessage("Rendering !! [current presure]", currentPresure, "kPa");
        }
    }

    // change state to ideal model
    statusPanel.setState(SystemEnums::SYSTEM_STATE_IDEAL);
    waterPump.stopMotor();
    printMessage("--------------------------------------------------------");
    printMessage("Redering completed !! at presure", currentPresure, "kPa");
    printMessage("--------------------------------------------------------");
}

bool isRenderNeeded(float target, float current)
{
    float normalizedPresure[2];
    normalizedPresure[0] = target - GlobalConstants ::NORM_PRESURE;
    normalizedPresure[1] = target + GlobalConstants ::NORM_PRESURE;
    return current < normalizedPresure[0] || current > normalizedPresure[1];
}

float getUpperBoundPresure(float target, float current)
{
    return target + GlobalConstants ::NORM_PRESURE;
}

float getLowerBoundPresure(float target, float current)
{
    return target - GlobalConstants ::NORM_PRESURE;
}
