#!/bin/bash

echo "Compiling..."
gcc -Wall stepper.h stepper.c main.c -lwiringPi -o step
echo "Copying to /usr/local/bin ..."
sudo cp step /usr/local/bin/step
