#include "periodic_led.h"

namespace ProjectWork2 {

PeriodicLed::PeriodicLed(PinName pin, int ms)
    : out(pin) {
    out = 0;
    ticker.attach(callback(this, &PeriodicLed::toggle), ms/1000.0); 
}

void PeriodicLed::toggle(void) {
    out = !out;
}

};