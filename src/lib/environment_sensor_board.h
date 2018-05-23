#pragma once

#include "transceiver.h"
#include "sensor_data.h"
#include "temperature_humidity_sensor.h"
#include "PIR_Sensor.h"

class EnvironmentSensorBoard{

    public:

    EnvironmentSensorBoard(Transceiver * inputTransceiver);

    void update();
    SensorData get_data();



    private:

    Transceiver * transceiver;

    // 3 sensoren

    TemperatureHumidity * temperatureSensor;
    PIRSensor motionSensor;
    I2C sensorI2C;
};