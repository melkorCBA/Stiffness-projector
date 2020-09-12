#ifndef StatusPanel_H
#define StatusPanel_H

class StatusPanel
{
    bool status;
    int state;
    int stateIdealPin;
    int stateRenderingPin;
    int statusPin;

public:
    StatusPanel();

    void setStatus(bool status);

    bool getStatus();

    void setState(int state);
    int getState();
};
#endif
