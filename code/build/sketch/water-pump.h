#ifndef WaterPump_H
#define WaterPump_H
class WaterPump
{
    int pin1;
    int pin2;
    int speedPin;
    int speed;

public:
    WaterPump();

    void leftSpin();

    void rightSpin();

    void stopMotor();
};
#endif