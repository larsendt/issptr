#pragma once

class Stepper {
    public:
        Stepper(int steps_per_rev, int a1_pin, int a2_pin, int b1_pin, int b2_pin);
        void rotate(float deg, float rpm);
        void nonblockingRotate(float deg, float rpm);
        void step();
        bool doneRotating();

    private:
        void sleep(int nsec); 
        void setPins(int a1, int a2, int b1, int b2);
        void step(int step_num, int direction, int ns_per_step);

        int _steps_per_rev;
        int _a1;
        int _a2;
        int _b1;
        int _b2;

        bool _rotating;
        int _total_steps;
        int _steps_done;
        int _ns_per_step;
        int _direction;
};
