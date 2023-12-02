#include <Arduino.h>
#import "gate.h"

gate::gate()
  {
    pinMode(PIN_A, OUTPUT);
    pinMode(PIN_B, OUTPUT);
    digitalWrite(PIN_A, LOW);
    digitalWrite(PIN_B, LOW);
    
    pinMode(LIMIT_SW_OPEN, INPUT);
    pinMode(LIMIT_SW_CLOSE, INPUT);
    
    set_status();
    
  }

String gate::get_status()
  {
    
    switch (status)
    {
      case gate_open:
        return GATE_STATUS_OPEN;
        break;
      case gate_close:
        return GATE_STATUS_CLOSED;
        break;
      case gate_in_operation:
        return GATE_STATUS_IN_OPERATION;
        break;
      case gate_error:
        return GATE_STATUS_ERROR;
        break;        
      default:
        return GATE_STATUS_UNKNOWN;
    }
  }
  
void gate::set_status()
  {
    if(digitalRead(LIMIT_SW_OPEN) == HIGH && digitalRead(LIMIT_SW_OPEN) == LOW)
      status = gate_open;

    if(digitalRead(LIMIT_SW_OPEN) == LOW && digitalRead(LIMIT_SW_OPEN) == HIGH)
      status = gate_close;

    if(digitalRead(LIMIT_SW_OPEN) == digitalRead(LIMIT_SW_OPEN))
      status = gate_error;
      
  }
  
void gate::open_gate()
  {
    status = gate_open;
    
  }
  
void gate::close_gate()
  {
    status = gate_close;
    
  }