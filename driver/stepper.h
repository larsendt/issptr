#pragma once

#include "sim_gpio.h"

class Stepper {
    public:
        Stepper(int steps_per_rev);
        void rotate(float deg, float rpm);

    private:
        int _steps_per_rev;
        SimGPIO _gpio;

        const int _dir_pin = 0;
        const int _step_pin = 1;
};
