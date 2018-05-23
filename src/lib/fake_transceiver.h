#pragma once

#include "transceiver.h"
#include <string>



class FakeTransceiver : public ProjectWork2::Transceiver {

    public:
        virtual void send_message(std::string message);
    
};