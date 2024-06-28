#ifndef MOTOR_H
#define MOTOR_H

void motor_setup();

void motor_forw();
void motor_back();
void motor_stop();
void motor_speed(unsigned int n); // Takes in a number from 0-255
void motor_drive(int n); // Takes in a number from -255 to 255. The sign will be the motor direction

#endif
