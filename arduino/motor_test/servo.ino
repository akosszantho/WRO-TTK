#include "servo.h"
#include "conf.h"
#include <Servo.h>

Servo servo1;

void servo_setup(){
  servo1.attach(SERVO_IN);
  
}

void servo_direction(unsigned int n){
  const unsigned int d = min(1023, n);
  const unsigned int angle = (unsigned int) ( (double) (d * 180 / 1023));
  servo1.write(d);
  
}

void servo_drive(int n){
  
}
