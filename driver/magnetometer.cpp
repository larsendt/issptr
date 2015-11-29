#include "magnetometer.h"
#include <iostream>
#include <stdint.h>
#include <wiringPiI2C.h>
#include <math.h>

Magnetometer::Magnetometer() {
    _fd = wiringPiI2CSetup(MAG_ADDR);

    if(_fd < 0) {
        std::cerr << "Failed to open I2C dev " << MAG_ADDR << std::endl;
        return;
    }

    write8(MAG_MR_REG_M, 0x0);

    uint8_t v = read8(MAG_CRA_REG_M);
    if(v != 0x10) {
        std::cerr << "Setup read returned unexpected value " << v << std::endl;
        return;
    }

    setGain(MAG_GAIN_2_5); 
}

float Magnetometer::compassDeg() {
    read();
    float PI = 3.1415926;
    return (atan2(_x, _y) * 180) / PI;
}

void Magnetometer::read() {
    while(read8(MAG_SR_REG_M) & 0x1 == 0) {
        std::cout << "data not ready" << std::endl;
    }

    uint8_t xhi = read8(MAG_OUT_X_H_M);
    uint8_t xlo = read8(MAG_OUT_X_L_M);
    uint8_t zhi = read8(MAG_OUT_Z_H_M);
    uint8_t zlo = read8(MAG_OUT_Z_L_M);
    uint8_t yhi = read8(MAG_OUT_Y_H_M);
    uint8_t ylo = read8(MAG_OUT_Y_L_M);

    _x = (int16_t)(xlo | ((int16_t)xhi << 8));
    _y = (int16_t)(ylo | ((int16_t)yhi << 8));
    _z = (int16_t)(zlo | ((int16_t)zhi << 8));

    std::cout << _x << " " << _y << " " << _z << std::endl;
}

void Magnetometer::write8(int reg, int val) {
    wiringPiI2CWriteReg8(_fd, reg, val);
}

int Magnetometer::read8(int reg) {
    return wiringPiI2CReadReg8(_fd, reg);
}

void Magnetometer::setGain(magGain_t gain) {
    write8(MAG_CRB_REG_M, gain);
}
