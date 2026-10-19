#include <Arduino.h>
#include "config.h"
#include "LDR.h"
#include "LED.h"
#include "BTN.h"

Ldr ldr_obj;
Button Button_obj;
Led Led_obj;



void setup(){

  Serial.begin(115200);
  Serial.println("setuped");

  ldr_obj.init();
  Button_obj.init();
  Led_obj.init();

}

void loop(){
 
  ldr_obj.poll();
  Button_obj.poll();
  Led_obj.handle_LDR(ldr_obj.get_state());
  Led_obj.handle_BTN(Button_obj.get_state());

}


