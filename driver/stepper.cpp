#include "stepper.h"
#include <iostream>
#include <time.h>

Stepper::Stepper(int steps_per_rev, int a1_pin, int a2_pin, int b1_pin, int b2_pin) {
    _steps_per_rev = steps_per_rev;
    _gpio = WiringPiGPIO();
    _a1 = a1_pin;
    _a2 = a2_pin;
    _b1 = b1_pin;
    _b2 = b2_pin;
}

void Stepper::rotate(float deg, float rpm) {
    int steps = (int)((deg / 360.0) * _steps_per_rev);
    steps = steps > 0 ? steps : -steps;

    float sec_per_rev = 60.0 / rpm;
    float sec_per_step = sec_per_rev / _steps_per_rev;
    int ns_per_step = (int)(sec_per_step * 1e9);

    for(int i = 0; i < steps/4; i++) {
        if(deg > 0) {
            setPins(1, 0, 1, 0);
            sleep(ns_per_step);
            setPins(0, 1, 1, 0);
            sleep(ns_per_step);
            setPins(0, 1, 0, 1);
            sleep(ns_per_step);
            setPins(1, 0, 0, 1);
            sleep(ns_per_step);
        }
        else {
            setPins(1, 0, 0, 1);
            sleep(ns_per_step);
            setPins(0, 1, 0, 1);
            sleep(ns_per_step);
            setPins(0, 1, 1, 0);
            sleep(ns_per_step);
            setPins(1, 0, 1, 0);
            sleep(ns_per_step);
        }
    }
}

void Stepper::setPins(int a1, int a2, int b1, int b2) {
    _gpio.set(_a1, a1);
    _gpio.set(_a2, a2);
    _gpio.set(_b1, b1);
    _gpio.set(_b2, b2);
}

void Stepper::sleep(int nsec) {
    struct timespec ts;
    ts.tv_sec = nsec / (int)1e9;
    ts.tv_nsec = nsec - (ts.tv_sec * (int)1e9);
    nanosleep(&ts, NULL);
}
