#include "lorawan_transceiver.h"

#define MBED_CONF_APP_LORAWAN_ENABLED 1
#define DEVICE_SPI 1
#include "lora_radio_helper.h"
#include "sensor_data_byte_serializer.h"

/*
 * Sets up an application dependent transmission timer in ms. Used only when Duty Cycling is off for testing
 */
#define TX_TIMER                        10000

namespace ProjectWork2 {

/**
 * Maximum number of retries for CONFIRMED messages before giving up
 */
#define CONFIRMED_MSG_RETRY_COUNTER     3

LoRaWANTransceiver::LoRaWANTransceiver(EventQueue * queue)
    : lorawan(radio) {
    this->ev_queue = queue;
    initialize_lora();
}

int LoRaWANTransceiver::initialize_lora(void) {
    // stores the status of a call to LoRaWAN protocol
    lorawan_status_t retcode;

    // Initialize LoRaWAN stack
    if (lorawan.initialize(ev_queue) != LORAWAN_STATUS_OK) {
        printf("\r\n LoRa initialization failed! \r\n");
        return -1;
    }

    printf("\r\n Mbed LoRaWANStack initialized \r\n");

    // prepare application callbacks
    callbacks.events = mbed::callback(this, &LoRaWANTransceiver::lora_event_handler);
    lorawan.add_app_callbacks(&callbacks);

    // Set number of retries in case of CONFIRMED messages
    if (lorawan.set_confirmed_msg_retries(CONFIRMED_MSG_RETRY_COUNTER)
                                          != LORAWAN_STATUS_OK) {
        printf("\r\n set_confirmed_msg_retries failed! \r\n\r\n");
        return -1;
    }

    printf("\r\n CONFIRMED message retries : %d \r\n",
           CONFIRMED_MSG_RETRY_COUNTER);

    // Enable adaptive data rate
    if (lorawan.enable_adaptive_datarate() != LORAWAN_STATUS_OK) {
        printf("\r\n enable_adaptive_datarate failed! \r\n");
        return -1;
    }

    printf("\r\n Adaptive data  rate (ADR) - Enabled \r\n");

    retcode = lorawan.connect();

    if (retcode == LORAWAN_STATUS_OK ||
            retcode == LORAWAN_STATUS_CONNECT_IN_PROGRESS) {
        printf("\r\n Connection - In Progress ...\r\n");
    } else {
        printf("\r\n Connection error, code = %d \r\n", retcode);
        return -1;
    }

    
    return 0;
}

void LoRaWANTransceiver::send(SensorData data) {

}

/**
 * Event handler
 */
void LoRaWANTransceiver::lora_event_handler(lorawan_event_t event) {
    switch (event) {
        case CONNECTED:
            printf("\r\n Connection - Successful \r\n");
            if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
                send_message();
            } else {
                // Not tested it yet with callback
                printf("This may fail. Not tested yet\r\n");
                ev_queue->call_every(TX_TIMER, callback(this, &LoRaWANTransceiver::send_message));
            }

            break;
        case DISCONNECTED:
            ev_queue->break_dispatch();
            printf("\r\n Disconnected Successfully \r\n");
            break;
        case TX_DONE:
            printf("\r\n Message Sent to Network Server \r\n");
            if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
                send_message();
            }
            break;
        case TX_TIMEOUT:
        case TX_ERROR:
        case TX_CRYPTO_ERROR:
        case TX_SCHEDULING_ERROR:
            printf("\r\n Transmission Error - EventCode = %d \r\n", event);
            // try again
            if (MBED_CONF_LORA_DUTY_CYCLE_ON) {
                send_message();
            }
            break;
        case RX_DONE:
            printf("\r\n Received message from Network Server \r\n");
            receive_message();
            break;
        case RX_TIMEOUT:
        case RX_ERROR:
            printf("\r\n Error in reception - Code = %d \r\n", event);
            break;
        case JOIN_FAILURE:
            printf("\r\n OTAA Failed - Check Keys \r\n");
            break;
        default:
            MBED_ASSERT("Unknown Event");
    }
}

/**
 * Sends a message to the Network Server
 */
void LoRaWANTransceiver::send_message(void)
{
    uint16_t packet_len;
    int16_t retcode;

    // SensorData data = board.get_data();
    SensorData data(1, 2, 3);
    packet_len = SensorDataByteSerializer::serialize(data, tx_buffer, LORAMAC_PHY_MAXPAYLOAD);

    // transceiver.send(data);

    retcode = lorawan.send(MBED_CONF_LORA_APP_PORT, tx_buffer, packet_len,
                           MSG_CONFIRMED_FLAG);

    if (retcode < 0) {
        retcode == LORAWAN_STATUS_WOULD_BLOCK ? printf("send - WOULD BLOCK\r\n")
                : printf("\r\n send() - Error code %d \r\n", retcode);
        return;
    }

    printf("\r\n %d bytes scheduled for transmission \r\n", retcode);
    memset(tx_buffer, 0, LORAMAC_PHY_MAXPAYLOAD);
}

/**
 * Receive a message from the Network Server
 */
void LoRaWANTransceiver::receive_message(void)
{
    int16_t retcode;
    retcode = lorawan.receive(MBED_CONF_LORA_APP_PORT, rx_buffer,
                              LORAMAC_PHY_MAXPAYLOAD,
                              MSG_CONFIRMED_FLAG|MSG_UNCONFIRMED_FLAG);

    if (retcode < 0) {
        printf("\r\n receive() - Error code %d \r\n", retcode);
        return;
    }

    printf(" Data:");

    for (uint8_t i = 0; i < retcode; i++) {
        printf("%x", rx_buffer[i]);
    }

    printf("\r\n Data Length: %d\r\n", retcode);

    memset(rx_buffer, 0, LORAMAC_PHY_MAXPAYLOAD);
}

};
