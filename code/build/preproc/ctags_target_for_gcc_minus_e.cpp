# 1 "/home/chatura/work/Arduino/stiffness projector/code/src/constants.cpp"
# 2 "/home/chatura/work/Arduino/stiffness projector/code/src/constants.cpp" 2
const float GlobalConstants ::MAT_A_BOUND_PRESURE = 4.0;
const float GlobalConstants ::MAT_B_BOUND_PRESURE = 4.0;
const float GlobalConstants ::MAT_C_BOUND_PRESURE = 4.0;
const float GlobalConstants ::MAT_D_BOUND_PRESURE = 4.0;
const int GlobalConstants ::RELAY_PIN_1 = 13;
const int GlobalConstants ::RELAY_PIN_2 = 14;
const int GlobalConstants::LN298_PIN_1 = 7;
const int GlobalConstants::LN298_PIN_2 = 8;
const int GlobalConstants::LN298_PMW_PIN = 10;
const int GlobalConstants ::PRESURE_SENSOR_PIN = 1;
const float GlobalConstants ::OFFSET_PRESURE = 0.483;
const int GlobalConstants::MOTOR_SPEED = 100;
const float GlobalConstants::NORM_PRESURE = 1.0;
const int GlobalConstants::STATE_IDEAL_PIN = 4;
const int GlobalConstants::STATE_RENDERING_PIN = 5;
const int GlobalConstants::STATUS_PIN = 6;
# 1 "/home/chatura/work/Arduino/stiffness projector/code/src/curve.ino"
//curves
float mat1[2]={1.0 ,12.0},
mat2[2]={1.5, 10.0},
 mat3[2]={2.0, 8.0};
# 1 "/home/chatura/work/Arduino/stiffness projector/code/src/l298n-test.ino"
// // connect motor controller pins to Arduino digital pins
// // motor one
// int enA = 10;
// int in1 = 7;
// int in2 = 8;
// // motor two
// int enB = 5;
// int in3 = 7;
// int in4 = 6;
// void setup()
// {
//     // set all the motor control pins to outputs
//     pinMode(enA, OUTPUT);
//     pinMode(enB, OUTPUT);
//     pinMode(in1, OUTPUT);
//     pinMode(in2, OUTPUT);
//     pinMode(in3, OUTPUT);
//     pinMode(in4, OUTPUT);
// }
// void demoOne()
// {
//     // this function will run the motors in both directions at a fixed speed
//     // turn on motor A
//     digitalWrite(in1, HIGH);
//     digitalWrite(in2, LOW);
//     // set speed to 200 out of possible range 0~255
//     analogWrite(enA, 200);

//     delay(2000);
//     // now change motor directions
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, HIGH);

//     delay(2000);
//     // now turn off motors
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, LOW);
// }
// void demoTwo()
// {
//     // this function will run the motors across the range of possible speeds
//     // note that maximum speed is determined by the motor itself and the operating voltage
//     // the PWM values sent by analogWrite() are fractions of the maximum speed possible
//     // by your hardware
//     // turn on motors
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, HIGH);

//     // accelerate from zero to maximum speed

//     for (int i = 150; i < 256; i++)
//     {
//         analogWrite(enA, i);

//         delay(500);
//     }
//     // decelerate from maximum speed to zero
//     for (int i = 255; i > 150; --i)
//     {
//         analogWrite(enA, i);

//         delay(500);
//     }

//     // now turn off motors
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, LOW);
// }
// void loop()
// {
//     demoTwo();
// }
# 1 "/home/chatura/work/Arduino/stiffness projector/code/src/main.ino"
// //sudo chmod a+rw /dev/ttyUSB0
// #include "projector.h"
# 4 "/home/chatura/work/Arduino/stiffness projector/code/src/main.ino" 2
# 5 "/home/chatura/work/Arduino/stiffness projector/code/src/main.ino" 2
# 6 "/home/chatura/work/Arduino/stiffness projector/code/src/main.ino" 2
# 7 "/home/chatura/work/Arduino/stiffness projector/code/src/main.ino" 2
# 8 "/home/chatura/work/Arduino/stiffness projector/code/src/main.ino" 2

float targetPresure;
void printMessage(String preMessage, float value, String postMessage);
WaterPump waterPump;
PresureSensor presureSensor;
StatusPanel statusPanel;

void setup()
{

    Serial.begin(9600);
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
        statusPanel.setState(SystemEnums::SYSTEM_STATE_RENDERING);
        waterPump.stopMotor();
        printMessage("redering completed !! presure", presureSensor.getCurrentPresureInPascal(), "kPa");

        // if (val == 'A')
        // {
        //     targetPresure = GlobalConstants::MAT_A_BOUND_PRESURE;
        //     printMessage("clicked", 0, "A");
        //     digitalWrite(13, HIGH);
        // }
        // if (val == 'B')
        // {
        //     targetPresure = GlobalConstants::MAT_B_BOUND_PRESURE;
        //     printMessage("clicked", 0, "B");
        //     digitalWrite(13, LOW);
        // }
        // if (val == 'C')
        // {
        //     targetPresure = GlobalConstants::MAT_C_BOUND_PRESURE;
        //     printMessage("clicked", 0, "C");
        // }
        // if (val == 'D')
        // {
        //     targetPresure = GlobalConstants::MAT_D_BOUND_PRESURE;
        //     printMessage("clicked", 0, "D");
        // }
    }
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
# 1 "/home/chatura/work/Arduino/stiffness projector/code/src/ss.ino"
// // //sudo chmod a+rw /dev/ttyUSB0

// int enA = 10;
// int in1 = 8;
// int in2 = 7;
// int solnoidPin=4;
// int an1 = 1;
// int speed = 250;
// const float OffSet = 0.483;
// float thumbArea = 0.0004;
// float currentPresure = 0.0;
// float targetPresure = 0.0;
// void printMessage(String preMessage, float value, String postMessage);

//     void setup()
// {

//   Serial.begin(9600);
//   pinMode(in1, OUTPUT);
//   pinMode(in2, OUTPUT);
//   pinMode(solnoidPin, OUTPUT);
//   pinMode(enA, OUTPUT);
//   digitalWrite(solnoidPin, HIGH);
//   analogWrite(enA, speed);
// }

// void loop()
// {

//   currentPresure = getPresureInPascal();
//   //message currentPresure
//   printMessage("current Presure", currentPresure, "Pa");

//   if (getPresureInPascal() > currentPresure + OffSet)
//   {

//     //message currentPresure change
//     printMessage("Presure change (dif)", getPresureInPascal() - currentPresure, "Pa");
//     targetPresure = getTargetPresure(currentPresure, getPresureInPascal(), thumbArea, mat1);
//     //message TargetPresure change
//     printMessage("Target Presure", targetPresure, "Pa");
//     digitalWrite(in1, HIGH);
//     digitalWrite(in2, LOW);
//     digitalWrite(solnoidPin, LOW);
//     while (targetPresure == getPresureInPascal())

//     {
//       //message Presure change precentage
//       printMessage("Adjusting Presure", (targetPresure - getPresureInPascal())*100 / (targetPresure - currentPresure), " Completed");

//     }

//   }
//   //message TargetPresure archived
//   printMessage("Target Presure archived", targetPresure, "Pa");
//   digitalWrite(solnoidPin, HIGH);
//   digitalWrite(in1, LOW);
//   digitalWrite(in2, LOW);
// }

// float getPresureInPascal()
// {
//   int P = ((analogRead(an1) * 5.00 / 1024) - OffSet) * 400;
//   return P;
// }

// float getTargetPresure(float initP, float endP, float thumbArea, float materialCurve[])
// {
//   //Y=mx+c
//   float appliedForce = (endP - initP) * thumbArea;
//   if (appliedForce > materialCurve[1])
//   {
//     appliedForce = materialCurve[1];
//   }
//   return (endP + appliedForce * materialCurve[0]);
// }

// void printMessage(String preMessage = "", float value = 0.0, String postMessage = "")
// {
//   Serial.println("");
//   Serial.print(preMessage);
//   Serial.print(" - ");
//   Serial.print(value);
//   Serial.print(postMessage);
//   Serial.println("");
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
