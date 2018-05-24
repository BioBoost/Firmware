#include "mbed.h"
#include "temperature_humidity_sensor.h"

    TemperatureHumidity::TemperatureHumidity(I2C* sensorI2C) :rhtSensor(sensorI2C){
    }

    void TemperatureHumidity::read_values() {
        if(!rhtSensor.check_availability(si7013, nullptr)){
            wait_ms(100);
            int ret = rhtSensor.measure(si7013, nullptr);
            wait_ms(100);
            if (!ret) {
                temperature = ((rhtSensor.get_temperature()/1000.0));
                humidity = ((rhtSensor.get_humidity()/1000));
            } else {
                printf("Failed to read temperature/humidity\r\n");
            }

        } else {
            printf("Failed to check avail temperature/humidity\r\n");
        }
    }

    int TemperatureHumidity::get_temperature(){
        read_values();
        return temperature;
    }

    int TemperatureHumidity::get_humidity(){
        read_values();
        return humidity;
    }



