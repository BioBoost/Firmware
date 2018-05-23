#include "terminal_transceiver.h"

#include <iostream>

namespace ProjectWork2 {

void TerminalTransceiver::send(SensorData data) {
    std::cout << "Humidity: " << std::to_string(data.getHumidity()) << "%" << std::endl;
    std::cout << "Temperature: " << std::to_string(data.getTemperature()) << "*C" << std::endl;
    std::cout << "Motion: " << std::to_string(data.getMotion()) << std::endl;
}

};