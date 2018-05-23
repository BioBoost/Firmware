#pragma once

#include "mbed.h"

namespace ProjectWork2 {

    class PeriodicLed {
        public:
            PeriodicLed(PinName pin, int ms=1000);
        
        private:
            void toggle(void);

        private:
            DigitalOut out;
            Ticker ticker;
    };

};