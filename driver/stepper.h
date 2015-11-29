#pragma once

class Stepper {
    public:
        Stepper(int steps_per_rev, int a1_pin, int a2_pin, int b1_pin, int b2_pin);
        void rotate(float deg, float rpm);

    private:
        void sleep(int nsec); 
        void setPins(int a1, int a2, int b1, int b2);

        int _steps_per_rev;
        int _a1;
        int _a2;
        int _b1;
        int _b2;
};
