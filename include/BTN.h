#pragma once

#include <Arduino.h>
#include "config.h"

class Button
{
private:
    enum BTN_STATES{
    NO_ACTIVE,
    ALARM_STATE,
    CRASH_STATE,
    };
    bool btn_state_alarm = false;
    bool btn_state_crash = false;
    BTN_STATES btn_state = NO_ACTIVE;             //змінна яка потрібна щоб керувати LED
    bool btn_was_pressed = false;
    bool btn_short_event = false;
    bool btn_long_event = false;
    bool btn_ispressed = false;
    u32_t lastTimeChangeBtn = 0;
    u32_t btn_timekeeper = 0;
    u32_t btn_time_press = 0;
    u32_t btn_time_release = 0;


public:
    void init();
    void poll();
    bool get_state();

};