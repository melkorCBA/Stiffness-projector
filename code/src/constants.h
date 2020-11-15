// Protect against multiple inclusions in the same source file
#ifndef CONSTANTS_H
#define CONSTANTS_H

class GlobalConstants
{

public:
    static const float MAT_A_BOUND_PRESURE;
    static const float MAT_B_BOUND_PRESURE;
    static const float MAT_C_BOUND_PRESURE;
    static const float MAT_D_BOUND_PRESURE;
    static const int RELAY_PIN_1;
    static const int RELAY_PIN_2;
    static const int LN298_PIN_1;
    static const int LN298_PIN_2;
    static const int LN298_PMW_PIN;
    static const int PRESURE_SENSOR_PIN;
    static const float OFFSET_PRESURE;
    static const float NORM_PRESURE;
    static const int MOTOR_SPEED;
    static const int STATUS_PIN;
    static const int STATE_IDEAL_PIN;
    static const int STATE_RENDERING_PIN;
    static const int BAUD_RATE;
};
#endif
