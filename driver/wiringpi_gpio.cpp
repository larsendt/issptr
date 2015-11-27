#include "wiringpi_gpio.h"
#include <wiringPi.h>

WiringPiGPIO::WiringPiGPIO() {
    wiringPiSetup();
}

void WiringPiGPIO::set(int pin, int value) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, value);
}
