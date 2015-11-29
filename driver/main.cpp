#include <iostream>
#include <stdlib.h>
#include "stepper.h"

int main(int argc, char *argv[]) {
    if(argc < 3) { 
        std::cout << "usage: " << argv[0] << " <deg> <rpm>" << std::endl;
        return 1;
    }

    Stepper s(513, 0, 1, 2, 3);
    s.rotate(atoi(argv[1]), atoi(argv[2]));
    return 0;
}
