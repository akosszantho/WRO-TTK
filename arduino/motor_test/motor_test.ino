#include "motor.h"
#include "conf.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Serial setup done");
  motor_setup();
  Serial.println("motor test start");

}

#define GOTIME 1500
#define STOPTIME 1000
#define GOSPEED 20

void loop() {
  Serial.println("Test start");
  
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

  Serial.println("Test done");
  
}
