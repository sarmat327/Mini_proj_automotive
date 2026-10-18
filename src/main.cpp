#include <Arduino.h>
#include "config.h"
#include "LDR.h"


u32_t lastTimeChangeLed = 0;

bool btn_state_alarm = false;
bool btn_state_crash = false;
bool btn_was_pressed = false;

bool btn_short_event = false;
bool btn_long_event = false;
bool btn_ispressed = false;
u32_t lastTimeChangeBtn = 0;
u32_t btn_timekeeper = 0;
u32_t btn_time_press = 0;
u32_t btn_time_release = 0;



bool led_white_state = false;
bool led_yellow_state = false;


void setup(){
  Serial.begin(115200);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  
  pinMode(LDR, INPUT);
  pinMode(BTN, INPUT_PULLDOWN);

  delay(1000);
  Serial.printf("Setup DONE \n");

  //ldr setup
  

}

void loop(){
  //Serial.printf("LDR rawData %d LDR filtered %d \n", ldr_rawData, ldr_filtered);



if(ldr_State == true)
{
  digitalWrite(LED_WHITE, HIGH);
} else {
  digitalWrite(LED_WHITE, LOW);
}


 
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
          btn_time_press = 0;
          btn_time_release = 0;
          Serial.println("ALARM is ON");
        } else 
        {
          btn_state_crash = false;
          btn_state_alarm = false;
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
          btn_time_press = 0;
          btn_time_release = 0;
          Serial.println("CRASH HAPPENED");
        } else 
        {
          btn_state_alarm = false;
          btn_state_crash = false;
          btn_time_press = 0;
          btn_time_release = 0;
          Serial.println("CRASH FIXED");
        }

        btn_timekeeper = 0;
      } 
  }

if(btn_state_alarm){
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
  }
if(btn_state_crash){
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
  }
  if (btn_state_alarm == false && btn_state_crash == false) digitalWrite(LED_YELLOW, LOW);

}


