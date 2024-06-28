#include "comms.h"
#include "conf.h"

void setup(){
  comms_setup();
  
}

void loop(){
  int d = comms_get();
  
  if(LEFT == d){
    Serial.println("left");
    
  } else if(RIGHT == d){
    Serial.println("right");
    
  } else {
    Serial.println("forward");
    
  }

  delay(500);
  
}
