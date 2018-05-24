#pragma once
#include "mbed.h"
#include "./SILABS_RHT.h"

class TemperatureHumidity{

    public:
        TemperatureHumidity(I2C* sensorI2C);
        void respondedCallback(void);
        int get_temperature();
        int get_humidity();

    private:
        void read_values();

    private:
    
        int temperature;
        int humidity;
        silabs::SILABS_RHT rhtSensor;   

};