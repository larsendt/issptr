#include <iostream>

#include "stepper.h"

int main(int argc, char *argv[]) {
    Stepper s(513);
    s.rotate(60, 200);
    return 0;
}
