#pragma once

#include "transceiver.h"
#include "mbed.h"
#include "lorawan/LoRaWANInterface.h"
#include "lorawan/system/lorawan_data_structures.h"
#include "environment_sensor_board.h"

namespace ProjectWork2 {

    class LoRaWANTransceiver : public Transceiver {

        public:
            LoRaWANTransceiver(EventQueue * queue, EnvironmentSensorBoard * board);

        public:
            virtual void send(SensorData data);

        private:
            int initialize_lora(void);
            void lora_event_handler(lorawan_event_t event);
            void send_message(void);
            void receive_message(void);

        private:
            EventQueue * ev_queue;

            // Transmit and receiver buffers of LoRa
            uint8_t tx_buffer[LORAMAC_PHY_MAXPAYLOAD];
            uint8_t rx_buffer[LORAMAC_PHY_MAXPAYLOAD];

            LoRaWANInterface lorawan;

            //Application specific callbacks
            lorawan_app_callbacks_t callbacks;

            // TODO: Needs to be refactored
            EnvironmentSensorBoard * board;

    };

};