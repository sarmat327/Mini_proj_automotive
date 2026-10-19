#include <Arduino.h>
#include "config.h"
#include "BTN.h"

void Button::init(){
    pinMode(BTN, INPUT_PULLDOWN);
}

void Button::poll(){
    if (millis() - lastTimeChangeBtn > BTN_PERIOD_MS) //цикл загального опитування кнопок, фільтр брязкоту
{
    lastTimeChangeBtn = millis();
    
    btn_ispressed = digitalRead(BTN);

    if(btn_ispressed == HIGH && !btn_was_pressed)
      {
        btn_was_pressed = true;
        btn_time_press = millis();
      }

    if(btn_ispressed == LOW && btn_was_pressed)
      {
        btn_was_pressed = false;
        btn_timekeeper = millis() - btn_time_press;
      }


    //Serial.printf("btn_timekeeper: %d btn_time_release: %d btn_time_press %d \n", btn_timekeeper, btn_time_release, btn_time_press);

    if(btn_timekeeper >= BTN_SHORT_PRESS_MS && btn_timekeeper < BTN_LONG_PRESS_MS)
      {
        if (!btn_state_alarm)
        {
          btn_state_crash = false;
          btn_state_alarm = true;
          btn_state = ALARM_STATE;
          btn_time_press = 0;
          btn_time_release = 0;
          Serial.println("ALARM is ON");
        } else 
        {
          btn_state_crash = false;
          btn_state_alarm = false;
          btn_state = NO_ACTIVE;
          btn_time_press = 0;
          btn_time_release = 0;
          Serial.println("ALARM is OFF");
        }

        btn_timekeeper = 0;

      }

     if(btn_timekeeper > BTN_LONG_PRESS_MS)
      {
       if(!btn_state_crash)
        {
          btn_state_alarm = false;
          btn_state_crash = true;
          btn_state = CRASH_STATE;
          btn_time_press = 0;
          btn_time_release = 0;
          Serial.println("CRASH HAPPENED");
        } else 
        {
          btn_state_alarm = false;
          btn_state_crash = false;
          btn_state = NO_ACTIVE;
          btn_time_press = 0;
          btn_time_release = 0;
          Serial.println("CRASH FIXED");
        }

        btn_timekeeper = 0;
      } 
  }
}

bool Button::get_state(){

  return btn_state;

}