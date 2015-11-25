#include "stepper.h"
#include <iostream>

Stepper::Stepper(int steps_per_rev) {
    _steps_per_rev = steps_per_rev;
    _gpio = SimGPIO();
}

void Stepper::rotate(float deg, float rpm) {
    int steps = (int)((deg / 360.0) * _steps_per_rev);
    steps = steps > 0 ? steps : -steps;

    float sec_per_rev = 60.0 / rpm;
    float sec_per_step = sec_per_rev / _steps_per_rev;
    int ns_per_step = (int)(sec_per_step * 1e9);

    if(deg > 0) {
        _gpio.set(_dir_pin, 0);
    }
    else {
        _gpio.set(_dir_pin, 1);
    }

    int toggle = 1;
    for(int i = 0; i < steps; i++) {
        std::cout << "sleep " << ns_per_step << " ns; toggle " << toggle << std::endl;
        _gpio.set(_step_pin, toggle);
        toggle = !toggle;
    }
}
