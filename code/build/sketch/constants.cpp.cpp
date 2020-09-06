#include <Arduino.h>
#line 12 "/home/chatura/work/Arduino/stiffness projector/code/src/main.ino"
void setup();
#line 23 "/home/chatura/work/Arduino/stiffness projector/code/src/main.ino"
void loop();
#line 0 "/home/chatura/work/Arduino/stiffness projector/code/src/main.ino"
#line 1 "/home/chatura/work/Arduino/stiffness projector/code/src/constants.cpp"
#include "constants.h"
const float GlobalConstants ::MAT_A_BOUND_PRESURE = 4.0;
const float GlobalConstants ::MAT_B_BOUND_PRESURE = 4.0;
const float GlobalConstants ::MAT_C_BOUND_PRESURE = 4.0;
const float GlobalConstants ::MAT_D_BOUND_PRESURE = 4.0;
const int GlobalConstants ::RELAY_PIN_1 = 13;
const int GlobalConstants ::RELAY_PIN_2 = 14;
const int GlobalConstants ::PRESURE_SENSOR_PIN = 1;
const float GlobalConstants ::OFFSET_PRESURE = 0.483;
#line 1 "/home/chatura/work/Arduino/stiffness projector/code/src/curve.ino"
//curves
float mat1[2]={1.0 ,12.0},
mat2[2]={1.5, 10.0},
 mat3[2]={2.0, 8.0};
#line 1 "/home/chatura/work/Arduino/stiffness projector/code/src/main.ino"
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
#line 1 "/home/chatura/work/Arduino/stiffness projector/code/src/print-message.ino"
void printMessage(String preMessage = "", float value = 0.0, String postMessage = "")
{
    Serial.println("");
    Serial.print(preMessage);
    Serial.print(" - ");
    Serial.print(value);
    Serial.print(postMessage);
    Serial.println("");
}
#line 1 "/home/chatura/work/Arduino/stiffness projector/code/src/relay-test.ino"
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
#line 1 "/home/chatura/work/Arduino/stiffness projector/code/src/ss.ino"
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
#line 1 "/home/chatura/work/Arduino/stiffness projector/code/src/test.ino"
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
