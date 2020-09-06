#ifndef PresureSensor_H
#define PresureSensor_H
class PresureSensor
{
    int inputPin;

public:
    PresureSensor();

    float getCurrentPresureInPascal();
};
#endif
