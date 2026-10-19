#include "config.h"
#include "LED.h"
#include <Arduino.h>


void Led::init(){
    pinMode(LED_WHITE, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
}


void Led::handle_LDR(bool ldr_State){
    if(ldr_State == true)
        {
            digitalWrite(LED_WHITE, HIGH);
        } else {
            digitalWrite(LED_WHITE, LOW);
        }
}
 
void Led::handle_BTN(u8_t btn_state){
    
    switch (btn_state){

        case NO_ACTIVE: digitalWrite(LED_YELLOW, LOW);
        break;

        case ALARM_STATE: 
                Serial.println("LED ALARM_STATE");
                if (millis() - lastTimeChangeLed > LED_BLINK_PERIOD_MS)
                 {
                    lastTimeChangeLed = millis();
                    if(!led_yellow_state)
                 {
                      digitalWrite(LED_YELLOW, HIGH);
                        led_yellow_state = true;
                 } else {
                        digitalWrite(LED_YELLOW, LOW);
                        led_yellow_state = false;
                    }
    
                 }
                 break;

        case CRASH_STATE: 

                Serial.println("LED CRASH_STATE");
                if (millis() - lastTimeChangeLed > LED_BLINK_CRASH_PERIOD_MS) 
                    {
                        lastTimeChangeLed = millis();
                        if(!led_yellow_state)
                    {
                        digitalWrite(LED_YELLOW, HIGH);
                        led_yellow_state = true;
                    } else {
                        digitalWrite(LED_YELLOW, LOW);
                        led_yellow_state = false;
                    }
                    }
                    break;
    }
    
 
}
