#pragma once
#include <Arduino.h>
#include "config.h"

class Led
{
private:
    u32_t lastTimeChangeLed = 0;
    bool led_white_state = false;
    bool led_yellow_state = false;
    
public:

    void init();
    void handle_LDR(bool ldr_State);
    void handle_BTN(u8_t state);
};