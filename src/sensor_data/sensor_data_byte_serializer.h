#pragma once

#include "sensor_data.h"

namespace ProjectWork2 {

    class SensorDataByteSerializer {

        public:
            static unsigned int serialize(SensorData data, uint8_t* buffer, unsigned int buffersize);

        private:
            static const int REQUIRED_PAYLOAD_SIZE = 5;

    };

};