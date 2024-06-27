#ifndef MOTOR_H
#define MOTOR_H

void motor_setup() __attribute__((noreturn));

void motor_forw() __attribute__((noreturn));
void motor_back() __attribute__((noreturn));
void motor_stop() __attribute__((noreturn));
void motor_speed(unsigned int n) __attribute__((noreturn)); // Takes in a number from 0-255
void motor_drive(int n) __attribute__((noreturn)); // Takes in a number from -255 to 255. The sign will be the motor direction

#endif
