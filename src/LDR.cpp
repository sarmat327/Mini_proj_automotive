#include "config.h"
#include "LDR.h"
#include <Arduino.h>


void Ldr::init()
{
    ldr_rawData = analogRead(LDR);
    ldr_filtered = ldr_rawData;
    ldr_filtered = ldr_filtered+ldr_alpha*(analogRead(LDR)-ldr_filtered);
}


void Ldr::poll()
{
    if(millis() - lastTimeChangeLdr >= LDR_PERIOD_MS)
    {
        ldr_rawData = analogRead(LDR);
        ldr_filtered = ldr_filtered+ldr_alpha*(ldr_rawData-ldr_filtered);
        lastTimeChangeLdr = millis();

  if(ldr_filtered >= LDR_THRESHOLD)
  {
      ldr_State = true;
  } else if(ldr_filtered <=LDR_THRESHOLD_DOWN) 
  {
       ldr_State = false;
  }

}

}

bool Ldr::get_state()
{
    return(ldr_State);
}
