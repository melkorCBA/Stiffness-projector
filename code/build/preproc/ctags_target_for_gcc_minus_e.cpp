# 1 "/home/chatura/work/Arduino/stiffness projector/code/src/constants.cpp"
# 2 "/home/chatura/work/Arduino/stiffness projector/code/src/constants.cpp" 2
const int GlobalConstants::BAUD_RATE = 9600;
const float GlobalConstants ::MAT_A_BOUND_PRESURE = 4.0;
const float GlobalConstants ::MAT_B_BOUND_PRESURE = 4.0;
const float GlobalConstants ::MAT_C_BOUND_PRESURE = 4.0;
const float GlobalConstants ::MAT_D_BOUND_PRESURE = 4.0;
const int GlobalConstants ::RELAY_PIN_1 = 13;
const int GlobalConstants ::RELAY_PIN_2 = 14;
const int GlobalConstants::LN298_PIN_1 = 2;
const int GlobalConstants::LN298_PIN_2 = 8;
const int GlobalConstants::LN298_PMW_PIN = 10;
const int GlobalConstants ::PRESURE_SENSOR_PIN = 1;
const float GlobalConstants ::OFFSET_PRESURE = 0.483;
const int GlobalConstants::MOTOR_SPEED = 100;
const float GlobalConstants::NORM_PRESURE = 1.0;
const int GlobalConstants::STATE_IDEAL_PIN = 4;
const int GlobalConstants::STATE_RENDERING_PIN = 5;
const int GlobalConstants::STATUS_PIN = 6;
# 1 "/home/chatura/work/Arduino/stiffness projector/code/src/l298n-test.ino"
// // connect motor controller pins to Arduino digital pins
// // motor one
// int enA = 10;
// int in1 = 7;
// int in2 = 8;
// // motor two

// void setup()
// {
//     // set all the motor control pins to outputs
//     pinMode(enA, OUTPUT);

//     pinMode(in1, OUTPUT);
//     pinMode(in2, OUTPUT);
// }

// void demoTwo()
// {
//     digitalWrite(in1, HIGH);
//     digitalWrite(in1, LOW);
//     analogWrite(enA, 200);
// }
// void loop()
// {
//     demoTwo();
// }
# 1 "/home/chatura/work/Arduino/stiffness projector/code/src/main.ino"
// //sudo chmod a+rw /dev/ttyUSB0
# 3 "/home/chatura/work/Arduino/stiffness projector/code/src/main.ino" 2
# 4 "/home/chatura/work/Arduino/stiffness projector/code/src/main.ino" 2
# 5 "/home/chatura/work/Arduino/stiffness projector/code/src/main.ino" 2
# 6 "/home/chatura/work/Arduino/stiffness projector/code/src/main.ino" 2
# 7 "/home/chatura/work/Arduino/stiffness projector/code/src/main.ino" 2

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
    pinMode(GlobalConstants::RELAY_PIN_1, 0x1);
    pinMode(GlobalConstants::RELAY_PIN_1, 0x1);
    pinMode(GlobalConstants::LN298_PMW_PIN, 0x1);

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
# 1 "/home/chatura/work/Arduino/stiffness projector/code/src/print-message.ino"
void printMessage(String preMessage = "", float value = 0.0, String postMessage = "")
{
    Serial.println("");
    Serial.print(preMessage);
    Serial.print(" - ");
    Serial.print(value);
    Serial.print(postMessage);
    Serial.println("");
}

void printMessage(String preMessage = "")
{
    Serial.println(preMessage);
}
# 1 "/home/chatura/work/Arduino/stiffness projector/code/src/relay-test.ino"
// //sudo chmod a+rw /dev/ttyUSB0

// int in1 = 13;
// int in2 = 12;

// void setup()
// {

//     // Serial.begin(9600);
//     pinMode(in1, OUTPUT);
//     pinMode(in2, OUTPUT);
// }

// void loop()
// {
//     digitalWrite(in1, HIGH);
//     delay(3000);
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, HIGH);
//     delay(1000);
//     digitalWrite(in2, LOW);
// }
# 1 "/home/chatura/work/Arduino/stiffness projector/code/src/test.ino"
// //sudo chmod a+rw /dev/ttyUSB0

// int enA = 10;
// int in1 = 8;
// int in2 = 7;
// int solnoidPin = 4;
// int an1 = 1;
// int speed = 255 const float OffSet = 0.483;
// float thumbArea = 0.0004;
// float currentPresure = 0.0;
// float targetPresure = 0.0;
// void printMessage(String preMessage, float value, String postMessage);

// void setup()
// {

//     Serial.begin(9600);
//     pinMode(in1, OUTPUT);
//     pinMode(in2, OUTPUT);
//     // pinMode(solnoidPin, OUTPUT);
//     pinMode(enA, OUTPUT);
//     // digitalWrite(solnoidPin, HIGH);
// }

// void loop()
// {
//     digitalWrite(in1, HIGH);
//     digitalWrite(in2, LOW);
//     analogWrite(enA, speed);
// }
