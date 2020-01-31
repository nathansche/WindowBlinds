# WindowBlinds
Using a RaspberryPi Zero W to remotely and automatically control the window blinds in my room. It's mainly a fun, cute little project that helps me get up in the morning. 

## How it works mechanically
My window blinds have a twisting mechanism to control the angle of the blinds. Twisting the shaft one way opens the blinds, twisting the other way closes it. Conveniently, the shaft has a hexagonal cross-sectional shape. A 3d printed gear is friction fitted on the shaft and meshes with another 3d printed gear friction fitted to a 28BYJ stepper motor. The motor is hooked up to a driver, which is in turn connected to the Raspberry Pi. The Raspberry Pi is connected to a stepper motor driver driving a 28BYJ stepper motor via pins 17, 27, 22, and 23. The motor is mounted to my window frame through command hook adhesive, and the whole thing stays together through a rubber band. 

## How it works in software
I made a small interface for the stepper motor, and then programmed the controls. I didn't want to have to compile a new program everytime I needed to tweak something, so I made simple arguments for a single command that would allow me to create a very basic sequential process for the motor to follow. Arguments are processed immediately and pushed onto a stack. This checks the arguments before executing anything on the motor, and minimizes processing time in between motor commands. One of the arguments is open, and I have a crontab set up to open the windows when I set my alarm. 
