#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "magnetometer.h"
#include "stepper.h"

int main(int argc, char *argv[]) {
    Stepper s(513, 0, 1, 2, 3);
    Magnetometer m;

    float cur_rot = 0;

    while(1) {
        float heading = m.compassDeg();
        float rotation = (int)(heading - cur_rot);
        std::cout << "heading: " << heading << " rotation: " << rotation << std::endl;
        if(rotation != 0) {
            s.rotate(rotation, 15);
            cur_rot = heading;
        }
        sleep(1);
    }
    return 0;
}
