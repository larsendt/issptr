#include "stepper.h"
#include <iostream>
#include <time.h>
#include <wiringPi.h>

Stepper::Stepper(int steps_per_rev, int a1_pin, int a2_pin, int b1_pin, int b2_pin) {
    _steps_per_rev = steps_per_rev;
    _a1 = a1_pin;
    _a2 = a2_pin;
    _b1 = b1_pin;
    _b2 = b2_pin;

    _rotating = false;

    wiringPiSetup();
    pinMode(_a1, OUTPUT);
    pinMode(_a2, OUTPUT);
    pinMode(_b1, OUTPUT);
    pinMode(_b2, OUTPUT);
}

void Stepper::nonblockingRotate(float deg, float rpm) {
    _rotating = true;

    _total_steps = (int)((deg / 360.0) * _steps_per_rev);
    _total_steps = _total_steps > 0 ? _total_steps : -_total_steps;
    _steps_done = 0;

    float sec_per_rev = 60.0 / rpm;
    float sec_per_step = sec_per_rev / _steps_per_rev;
    _ns_per_step = (int)(sec_per_step * 1e9);
    _direction = deg >= 0;
}

void Stepper::step() {
    if(!_rotating) {
        return;
    }
    else if(_steps_done == _total_steps) {
        _rotating = false;
        return;
    }

    _step(_steps_done, _direction, _ns_per_step);
    _steps_done += 1;
}

bool Stepper::doneRotating() {
    return !_rotating;
}

void Stepper::rotate(float deg, float rpm) {
    nonblockingRotate(deg, rpm);
    while(!doneRotating()) {
        step();
    }
}

void Stepper::setPins(int a1, int a2, int b1, int b2) {
    digitalWrite(_a1, a1);
    digitalWrite(_a2, a2);
    digitalWrite(_b1, b1);
    digitalWrite(_b2, b2);
}

void Stepper::sleep(int nsec) {
    struct timespec ts;
    ts.tv_sec = nsec / (int)1e9;
    ts.tv_nsec = nsec - (ts.tv_sec * (int)1e9);
    nanosleep(&ts, NULL);
}

void Stepper::_step(int step_num, int direction, int ns_per_step) {
    if(direction > 0) {
        switch(step_num % 4) {
            case 0:
                setPins(1, 0, 1, 0);
                break;
            case 1:
                setPins(0, 1, 1, 0);
                break;
            case 2:
                setPins(0, 1, 0, 1);
                break;
            case 3:
                setPins(1, 0, 0, 1);
                break;
            default:
                std::cerr << "Default case in step pattern!!! THIS SHOULD NEVER HAPPEN" << std::endl;
        }
    }
    else {
        switch(step_num % 4) {
            case 0:
                setPins(1, 0, 0, 1);
                break;
            case 1:
                setPins(0, 1, 0, 1);
                break;
            case 2:
                setPins(0, 1, 1, 0);
                break;
            case 3:
                setPins(1, 0, 1, 0);
                break;
            default:
                std::cerr << "Default case in step pattern!!! THIS SHOULD NEVER HAPPEN" << std::endl;
        }
    }
    sleep(ns_per_step);
}
