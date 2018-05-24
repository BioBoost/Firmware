#pragma once

#include "sensor_data.h"

namespace ProjectWork2 {

    class Transceiver {
        public:
            virtual void send(SensorData data) = 0;
    };

};
