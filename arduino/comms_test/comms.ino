#include "comms.h"
#include "conf.h"

void comms_setup(){
  Serial.begin(9600);
  
}

unsigned int comms_get(){
  char c = 'n';
  int d = FORWARD;

  while(Serial.available()){
    c = Serial.read();
    if('\n' == c){
      break;
      
    } else if('l' == c){
      d = LEFT;
    
    } else if('r' == c){
      d = RIGHT;
    
    } else {
      d = FORWARD;
      
    }
  }

  return d;

}
