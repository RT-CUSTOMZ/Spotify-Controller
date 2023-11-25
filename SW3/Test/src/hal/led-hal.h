#pragma once
#include <Arduino.h>

inline void ledOn (const uint8_t pinnumber) {
    digitalWrite(pinnumber, HIGH);
}

inline void ledOff (const uint8_t pinnumber) {
    digitalWrite(pinnumber, LOW);
}
