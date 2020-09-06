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