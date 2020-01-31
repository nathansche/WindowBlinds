#ifndef WINDOW_STEPPER
#define WINDOW_STEPPER

#define DEFAULT_STEP_DELAY 825

/*
Default pin setup on BCM
    defaultPins[0] = coil A1
    defaultPins[1] = coil A2
    defaultPins[2] = coil B1
    defaultPins[3] = coil B2
*/
extern const int defaultPins[4];

/*
 *Setup the motor with default pins
 *   A setup function must be called before using any other function
 */
void stepperSetup();

/*
 *Setup the motor with user specified pins
 */
void stepperManualSetup(int, int, int, int);

/*
 *Set the delay in between motor steps, in microseconds
 */
void setDelay(unsigned int);

/*
 *Get the currently set delay in between motor steps, in microseconds
 */
unsigned int getDelay(void);

/*
 *Halts program execution for specified number of milliseconds
 *  Useful when changing directions quickly
 */
void sleep(unsigned int);

/*
 *Steps forward specified steps using given delay (in microseconds) in between steps
 */
void forwardDelay(unsigned int delay, int steps);

/*
 *Steps backward specified steps using given delay (in microseconds) in between steps
 */
void backwardsDelay(unsigned int delay, int steps);

/*
 *Steps forward specified steps with set delay
 */
void forward(int);

/*
 *Steps backward specified steps with set delay
 */
void backwards(int);

/*
 *Set motor to powered off state
 *   Should be called once a given movement is done 
 *   Do not need to re-setup the motor/pi before moving again
 */
void powerOff();

#endif
