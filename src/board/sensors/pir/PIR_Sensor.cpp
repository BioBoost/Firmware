#include "pir_sensor.h"
#include "mbed.h"

    PIRSensor::PIRSensor(PinName pin) : sensorInterrupt(pin) {
        sensorInterrupt.mode(PullDown);
        sensorInterrupt.rise(callback(this, &PIRSensor::positive_edge_detected));
        sensorInterrupt.fall(callback(this, &PIRSensor::negative_edge_detected));
        this->state = LOW;
    }

    void PIRSensor::start(){
        lowtime = 0;
        hightime = 0;
        timer.reset();
        timer.start();
    }

    void PIRSensor::stop(){
        timer.stop();
        if (state==LOW){
            int deltaT = get_delta();
            lowtime += deltaT;
        }else{
            int deltaT = get_delta();
            hightime += deltaT;
        }
    }

    void PIRSensor::positive_edge_detected() {
        state = HIGH;
        int deltaT = get_delta();
        lowtime += deltaT;
    }

    void PIRSensor::negative_edge_detected() {
        state = LOW;
        int deltaT = get_delta();
        hightime += deltaT;
    }
    
    int PIRSensor::get_percentage_movement(){
        int percentage = (1.0*hightime/(hightime+lowtime))*100;
        return percentage;
    }
        
    int PIRSensor::get_delta(){
        int deltaT = timer.read_ms() - lowtime - hightime;
        return deltaT;
    }