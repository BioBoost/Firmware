#pragma once
#include "mbed.h"

class PIRSensor{

    enum State {HIGH,LOW};

     public:
         PIRSensor(PinName pin);
         void positive_edge_detected();
         void negative_edge_detected();
         void start();
         void stop();
         int get_percentage_movement();

    private:

        int get_delta();

     private:

        InterruptIn sensorInterrupt;
        Timer timer;
        int lowtime;
        int hightime;
        State state;
};