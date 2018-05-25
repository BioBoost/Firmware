#include "mbed.h"
#include <iostream>
#include "simple_logger.h"

using namespace std;

#include "events/EventQueue.h"

// Application helpers
#include "terminal_transceiver.h"
#include "lorawan_transceiver.h"
#include "periodic_led.h"
#include "environment_sensor_board.h"

/**
 * Maximum number of events for the event queue.
 * 16 is the safe number for the stack events, however, if application
 * also uses the queue for whatever purposes, this number should be increased.
 */
#define MAX_NUMBER_OF_EVENTS            16

/**
* This event queue is the global event queue for both the
* application and stack. To conserve memory, the stack is designed to run
* in the same thread as the application and the application is responsible for
* providing an event queue to the stack that will be used for ISR deferment as
* well as application information event queuing.
*/
static EventQueue ev_queue(MAX_NUMBER_OF_EVENTS * EVENTS_EVENT_SIZE);

Serial pc(USBTX, USBRX); // tx, rx

// Why does it fail here ?
// SimpleLogger::Logger::get_instance().register_writer(new SimpleLogger::TerminalLogWriter());

ProjectWork2::PeriodicLed alive1(PC_8, 500);
ProjectWork2::PeriodicLed alive2(PC_9, 1332);
ProjectWork2::PeriodicLed alive3(PC_10, 2565);

ProjectWork2::TerminalTransceiver transceiver;
EnvironmentSensorBoard board(&transceiver);

int main (void)
{
    SimpleLogger::Logger::get_instance().register_writer(new SimpleLogger::TerminalLogWriter());
    Log.info("Booting LoRaWAN motion detection board");


    cout << "Creating a LoRaWAN transceiver" << endl;
    ProjectWork2::LoRaWANTransceiver loraTransceiver(&ev_queue, &board);

    // make your event queue dispatching events forever
    ev_queue.dispatch_forever();

    while(true) {}

    return 0;
}
