#include "motor.h"
#include "conf.h"

void motor_setup(){
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);

  motor_stop();
  
}

void motor_forward(){
  digitalWrite(MOTOR_IN1, LOW);
  
}

void motor_backward(){
  digitalWrite(MOTOR_IN1, HIGH);
  
}

void motor_speed(unsigned int n){
  const unsigned int speed = min(255, n);
  analogWrite(MOTOR_IN2, speed);
  
}

void motor_stop(){
  digitalWrite(MOTOR_IN1, LOW);
  analogWrite(MOTOR_IN2, 0);
  
}

void motor_drive(int n){
  const unsigned int speed = abs(n);
  if(0 == n){
    motor_stop();
  }
  else if(0 > n){
    motor_backward();
    motor_speed(speed);
    
  } else {
    motor_forward();
    motor_speed(speed);
    
  }
}
