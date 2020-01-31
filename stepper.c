#include <wiringPi.h>
#include "stepper.h"

const int defaultPins[4] = {17, 27, 22, 23};
int pins[4] = {17, 27, 22, 23};

int Seq[8][4] = { 
         {1,0,0,0},
         {1,1,0,0},
         {0,1,0,0},
         {0,1,1,0},
         {0,0,1,0},
         {0,0,1,1},
         {0,0,0,1},
         {1,0,0,1}
    };

int stepCount = 8;
unsigned int delayTime = DEFAULT_STEP_DELAY; //microseconds

unsigned int getDelay()
{
    return delayTime;
}
void setDelay(unsigned int d)
{
    delayTime = d;
}
void sleep(unsigned int s)
{
    delay(s);
}

void stepperManualSetup(int pin0, int pin1, int pin2, int pin3)
{
    wiringPiSetupGpio();
    pins[0] = pin0;
    pins[1] = pin1;
    pins[2] = pin2;
    pins[3] = pin3;
    for(int i = 0; i < 4; ++i)
    {
        pinMode(pins[i], OUTPUT);
    }
}
void stepperSetup()
{
    stepperManualSetup(defaultPins[0], defaultPins[1], defaultPins[2], defaultPins[3]);
}
void setStep(int s1, int s2, int s3, int s4)
{
    digitalWrite(pins[0], s1);
    digitalWrite(pins[1], s2);
    digitalWrite(pins[2], s3);
    digitalWrite(pins[3], s4);
}

void forwardDelay(unsigned int delay, int steps)
{
    for(int i = 0; i < steps; ++i)
    {
        for(int j = 0; j < stepCount; ++j)
        {
            setStep(Seq[j][0], Seq[j][1], Seq[j][2], Seq[j][3]);
            delayMicroseconds(delay);
        }
    }
}

void backwardsDelay(unsigned int delay, int steps)
{
    for(int i = 0; i < steps; ++i)
    {
        for(int j = stepCount - 1; j >=0; --j)
        {
            setStep(Seq[j][0], Seq[j][1], Seq[j][2], Seq[j][3]);
            delayMicroseconds(delay);
        }
    }
}

void forward(int steps)
{
    forwardDelay(delayTime, steps);
}
void backwards(int steps)
{
    backwardsDelay(delayTime, steps);
}
void powerOff()
{
    setStep(0,0,0,0);
}

