#include "environment_sensor_board.h"

EnvironmentSensorBoard::EnvironmentSensorBoard(ProjectWork2::Transceiver * inputTransceiver)
    : motionSensor(PA_9), sensorI2C(PC_1, PC_0) {

    this->transceiver = inputTransceiver;
    temperatureSensor = new TemperatureHumidity(&sensorI2C);
}

void EnvironmentSensorBoard::update(){
    SensorData data = get_data();
    transceiver->send(data);
}

SensorData EnvironmentSensorBoard::get_data(void) {
    double temperature = temperatureSensor->get_temperature();
    int motion = motionSensor.get_percentage_movement();
    double humidity = temperatureSensor->get_humidity();

    SensorData data(temperature, motion, humidity);
    return data;
}