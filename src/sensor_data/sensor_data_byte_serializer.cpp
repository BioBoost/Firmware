#include "sensor_data_byte_serializer.h"

namespace ProjectWork2 {

    unsigned int SensorDataByteSerializer::serialize(SensorData data, uint8_t* buffer, unsigned int buffersize) {
        if (buffersize >= REQUIRED_PAYLOAD_SIZE) {
            int temperature = data.get_temperature();
            int motion = data.get_motion();
            
            buffer[0] = (uint8_t) temperature >> 8;
            buffer[1] = (uint8_t) temperature & 0xFF;
            buffer[2] = (uint8_t) data.get_humidity();
            buffer[3] = (uint8_t) motion >> 8;
            buffer[4] = (uint8_t) motion & 0xFF;

            return REQUIRED_PAYLOAD_SIZE;
        }

        return 0;
    }

};