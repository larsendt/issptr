#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "magnetometer.h"
#include "stepper.h"

int main(int argc, char *argv[]) {
    Stepper s1(513, 0, 1, 2, 3);
    Stepper s2(513, 4, 5, 6, 7);
    Magnetometer m;

    float cur_rot = 0;

    while(1) {
        float heading = m.compassDeg();
        float rotation = (int)(heading - cur_rot);
        std::cout << "heading: " << heading << " rotation: " << rotation << std::endl;
        if(rotation != 0) {
            s1.nonblockingRotate(rotation, 15);
            s2.nonblockingRotate(rotation, 15);
            while((!s1.doneRotating()) || (!s2.doneRotating())) {
                s1.step();
                s2.step();
            }
            cur_rot = heading;
        }
        sleep(1);
    }
    return 0;
}
