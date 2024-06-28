#include "motor.h"
#include "conf.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Serial setup done");
  motor_setup();
  Serial.println("motor test start");

}



void loop() {
  motor_test();
  servo_sweep_test();
  servo_minmax_test();
  
}

void motor_test(){
#define GOTIME 1500
#define STOPTIME 1000
#define GOSPEED 20

  Serial.println("motor test start");
  
  Serial.println("forward");
  motor_drive(GOSPEED);
  delay(GOTIME);

  Serial.println("stop");
  motor_drive(0);
  delay(STOPTIME);
  
  Serial.println("backward");
  motor_drive(-GOSPEED);
  delay(GOTIME);

  Serial.println("stop");
  motor_drive(0);
  delay(STOPTIME);

  Serial.println("motor test done");
  
}


#define SERVO_MIN 0
#define SERVO_MAX 1023
#define SERVO_TICK_WAIT 10

void servo_sweep_test(){
  Serial.println("servo sweep test start");

  Serial.println("forward");
  for(int i=SERVO_MIN; i<SERVO_MAX; i++){
    servo_direction(i);
    delay(SERVO_TICK_WAIT);
    
  }
  
  Serial.println("forward");
  for(int i=SERVO_MAX; i<SERVO_MIN; i--){
    servo_direction(i);
    delay(SERVO_TICK_WAIT);
    
  }
  
  Serial.println("servo sweep test done");
  
}

void servo_minmax_test(){
  Serial.println("servo min/max test start");

  Serial.println("min");
  servo_direction(SERVO_MIN);
  delay(1000);
  
  Serial.println("max");
  servo_direction(SERVO_MAX);
  delay(1000);
  
  Serial.println("servo min/max test done");
  
}
