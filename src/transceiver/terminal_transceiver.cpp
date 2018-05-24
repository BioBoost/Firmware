#include "terminal_transceiver.h"

#include <iostream>

namespace ProjectWork2 {

void TerminalTransceiver::send(SensorData data) {
    std::cout << "Humidity: " << std::to_string(data.get_humidity()) << "%" << std::endl;
    std::cout << "Temperature: " << std::to_string(data.get_temperature()) << "*C" << std::endl;
    std::cout << "Motion: " << std::to_string(data.get_motion()) << std::endl;
}

};