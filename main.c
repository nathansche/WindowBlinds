#include <stdlib.h>
#include "stepper.h"
#include <stdio.h>

#define FORWARD 'f'
#define BACKWARD 'b'
#define SLEEP 'w'
#define OPEN 'o'
#define CLOSE 'c'

#define OPEN_STEPS 5000
#define CLOSE_STEPS 6000

const char* message = "Options:\n"
" -f{steps}\t\tGoes forward specified number of steps\n"
" -b{steps}\t\tGoes backwards specified number of steps\n"
" -w{milliseconds}\tWaits specified number of milliseconds\n"
" -o\t\t\tUses default numbers to open windows\n"
" -c\t\t\tUses default numbers to close windows\n";
const char* PROGRAM_NAME;
typedef struct _Option
{
    char type;
    unsigned int argument;
} Option;

Option* optionStack = NULL;
Option* optionStackTop = NULL;

int makeOption(char* input)
{
    switch(*input)
    {
        case FORWARD:
            optionStackTop->type = FORWARD;
            break;
        case BACKWARD:
            optionStackTop->type = BACKWARD;
            break;
        case SLEEP:
            optionStackTop->type = SLEEP;
            break;
        case OPEN:
            optionStackTop->type = OPEN;
            break;
        case CLOSE:
            optionStackTop->type = CLOSE;
            break;
        default:
            printf("Unknown Option: %c\n", *input);
            return 1;
    }
    input++;
    optionStackTop->argument = 0;
    if(sscanf(input, "%u", &(optionStackTop->argument)) == 0)
    {
        if(optionStackTop->type != OPEN && optionStackTop->type != CLOSE)
        {
            if(*input == '\0')
                printf("Numerical argument must be specified for option %c\n", optionStackTop->type);
            else
                printf("Argument \"%s\" must be a positive number\n", input);
            return 1;
        }
    }
    ++optionStackTop;
    return 0;
}

void badInput()
{
    if(optionStack != NULL)
        free(optionStack);
    printf("%s ", PROGRAM_NAME);
    printf("%s", message);
}
int main(int argc, char *argv[])
{
    PROGRAM_NAME = argv[0];
    stepperSetup();
    if(argc == 1)
    {
        badInput();
        return 1;
    }
    optionStack = (Option *) malloc(sizeof(Option) * (argc - 1));
    optionStackTop = optionStack;
 
    while(--argc)
    {
        ++argv;
        if(*argv == NULL || **argv != '-')
        {
            badInput();
            return 1;
        }
        else
        {
            if(makeOption(++(*argv)) == 1)
            {
                badInput();
                return 1;
            }
        }
    }
    for(Option* o = optionStack; o != optionStackTop; ++o)
    {
        switch(o->type)
        {
            case FORWARD:
                forward(o->argument);
                break;
            case BACKWARD:
                backwards(o->argument);
                break;
            case SLEEP:
                powerOff();
                sleep(o->argument);
                break;
            case OPEN:
                backwards(OPEN_STEPS);
                break;
            case CLOSE:
                forward(CLOSE_STEPS);
                break;
        }
    }
    powerOff();
    free(optionStack);
    return 0;
}
