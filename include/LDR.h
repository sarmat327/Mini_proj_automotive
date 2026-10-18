#pragma once

#include <Arduino.h>
#include "config.h"

class Ldr
{
private:
   
    bool  ldr_State = false;
    u32_t lastTimeChangeLdr = 0;
    u16_t ldr_resolution = 4095;
    u16_t ldr_rawData = 0; //  max 4095
    u16_t ldr_filtered = 0;
    float ldr_alpha = 0.1f; //коефіцієнт швидкості реакції фільтра



public:
    void init();
    void poll();
    bool get_state();
};