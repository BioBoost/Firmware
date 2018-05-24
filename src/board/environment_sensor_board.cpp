#include "environment_sensor_board.h"

EnvironmentSensorBoard::EnvironmentSensorBoard(ProjectWork2::Transceiver * inputTransceiver)
    : motionSensor(PA_9), sensorI2C(PC_1, PC_0) {

    this->transceiver = inputTransceiver;
    temperatureSensor = new TemperatureHumidity(&sensorI2C);
    motionSensor.start();
}

void EnvironmentSensorBoard::update() {
    ProjectWork2::SensorData data = get_data();
    transceiver->send(data);
}

ProjectWork2::SensorData EnvironmentSensorBoard::get_data(void) {
    double temperature = temperatureSensor->get_temperature();
    double humidity = temperatureSensor->get_humidity();
    
    motionSensor.stop();
    int motion = motionSensor.get_percentage_movement();
    motionSensor.start();

    ProjectWork2::SensorData data(temperature, motion, humidity);
    return data;
}