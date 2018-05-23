#pragma once

#include "transceiver.h"

namespace ProjectWork2 {

    class TerminalTransceiver : public Transceiver {

        public:
            virtual void send(SensorData data);

    };

};

