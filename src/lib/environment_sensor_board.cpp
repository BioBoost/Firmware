#include "environment_sensor_board.h"



EnvironmentSensorBoard::EnvironmentSensorBoard(ProjectWork2::Transceiver * inputTransceiver)
: motionSensor(PA_9), sensorI2C(PC_1, PC_0) //PC_1=SDA, PC_0=SCL
{
    this->transceiver = inputTransceiver;
    temperatureSensor = new TemperatureHumidity(&sensorI2C);
}


void EnvironmentSensorBoard::update(){
    // double temperature = temperatureSensor.get_temperature_value();
    // int motion = motionSensor.get_percentage_movement();
    // double humidity = humiditySensor.get_humidity_value();   



    // SensorData data(temperature, motion, humidity);


    //transceiver->send_message(data);
}

SensorData EnvironmentSensorBoard::get_data (){
    double temperature = temperatureSensor->get_temperature();
    int motion = motionSensor.get_percentage_movement();
    double humidity = temperatureSensor->get_humidity();

    SensorData data (temperature, motion, humidity);
    return data;
}






