# 1 "/home/chatura/work/Arduino/stiffness projector/code/src/curve.ino"
//curves
float mat1[2]={1.0 ,12.0},
mat2[2]={1.5, 10.0},
 mat3[2]={2.0, 8.0};
# 1 "/home/chatura/work/Arduino/stiffness projector/code/src/ss.ino"
//sudo chmod a+rw /dev/ttyUSB0

int enA = 10;
int in1 = 8;
int in2 = 7;
int solnoidPin=4;
int an1 = 1;
int speed = 250;
const float OffSet = 0.483;
float thumbArea = 0.0004;
float currentPresure = 0.0;
float targetPresure = 0.0;
void printMessage(String preMessage, float value, String postMessage);

    void setup()
{

  Serial.begin(9600);
  pinMode(in1, 0x1);
  pinMode(in2, 0x1);
  pinMode(solnoidPin, 0x1);
  pinMode(enA, 0x1);
  digitalWrite(solnoidPin, 0x1);
  analogWrite(enA, speed);
}

void loop()
{

  currentPresure = getPresureInPascal();
  //message currentPresure
  printMessage("current Presure", currentPresure, "Pa");

  if (getPresureInPascal() > currentPresure + OffSet)
  {

    //message currentPresure change
    printMessage("Presure change (dif)", getPresureInPascal() - currentPresure, "Pa");
    targetPresure = getTargetPresure(currentPresure, getPresureInPascal(), thumbArea, mat1);
    //message TargetPresure change
    printMessage("Target Presure", targetPresure, "Pa");
    digitalWrite(in1, 0x1);
    digitalWrite(in2, 0x0);
    digitalWrite(solnoidPin, 0x0);
    while (targetPresure == getPresureInPascal())

    {
      //message Presure change precentage
      printMessage("Adjusting Presure", (targetPresure - getPresureInPascal())*100 / (targetPresure - currentPresure), " Completed");


    }

  }
  //message TargetPresure archived
  printMessage("Target Presure archived", targetPresure, "Pa");
  digitalWrite(solnoidPin, 0x1);
  digitalWrite(in1, 0x0);
  digitalWrite(in2, 0x0);
}

float getPresureInPascal()
{
  int P = ((analogRead(an1) * 5.00 / 1024) - OffSet) * 400;
  return P;
}

float getTargetPresure(float initP, float endP, float thumbArea, float materialCurve[])
{
  //Y=mx+c
  float appliedForce = (endP - initP) * thumbArea;
  if (appliedForce > materialCurve[1])
  {
    appliedForce = materialCurve[1];
  }
  return (endP + appliedForce * materialCurve[0]);
}

void printMessage(String preMessage = "", float value = 0.0, String postMessage = "")
{
  Serial.println("");
  Serial.print(preMessage);
  Serial.print(" - ");
  Serial.print(value);
  Serial.print(postMessage);
  Serial.println("");
}
