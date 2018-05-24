#include "sensor_data.h"

namespace ProjectWork2 {

SensorData::SensorData(void)
   : SensorData(0, 0, 0) {
}

SensorData::SensorData(double temperature, int motion, double humidity) {
    set_temperature(temperature);
    set_humidity(humidity);
    set_motion(motion);
}

double SensorData::get_temperature(void) const {
    return temperature;
}

double SensorData::get_humidity(void) const {
    return humidity;
}

int SensorData::get_motion(void) const {
    return motion;
}

void SensorData::set_temperature(double temperature) {
    this->temperature = temperature;
}

void SensorData::set_humidity(double humidity) {
    this->humidity = humidity;
}

void SensorData::set_motion(int motion) {
    this->motion = motion;
}

std::string SensorData::to_string(void) const {
    return "Temperature: " + std::to_string(temperature) + "*C,\r\n"
            + "Humidity: " + std::to_string(humidity) + "%,\r\n"
            + "Motion: " + std::to_string(motion);
}

std::string SensorData::to_json(void) const {
    return  "{\"temperature\": {\"value\":" + std::to_string(temperature) + ", \"unit\": \"°C\"}, " +
            "\"motion\": " + std::to_string(motion) + ", "
            "\"humidity\": {\"value\":" + std::to_string(humidity) + ", \"unit\": \"%\"}}" ;
}

};
