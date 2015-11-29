#pragma once

class Magnetometer {
    public:
        Magnetometer();
        int x() { read(); return _x; }
        int y() { read(); return _y; }
        int z() { read(); return _z; }
        float compassDeg();


        typedef enum 
        {
            MAG_CRA_REG_M = 0x0,
            MAG_CRB_REG_M = 0x1,
            MAG_MR_REG_M  = 0x2,
            MAG_OUT_X_H_M = 0x3,
            MAG_OUT_X_L_M = 0x4,
            MAG_OUT_Z_H_M = 0x5,
            MAG_OUT_Z_L_M = 0x6,
            MAG_OUT_Y_H_M = 0x7,
            MAG_OUT_Y_L_M = 0x8,
            MAG_SR_REG_M = 0x9,
            MAG_IRA_REG_M = 0xA,
            MAG_IRB_REG_M = 0xB,
            MAG_IRC_REG_M = 0xC,
            MAG_TEMP_OUT_H_M = 0x31,
            MAG_TEMP_OUT_L_M = 0x32,
        } magRegisters_t;

        typedef enum
        {
            MAG_GAIN_1_3 = 0x20,
            MAG_GAIN_1_9 = 0x40,
            MAG_GAIN_2_5 = 0x60,
            MAG_GAIN_4_0 = 0x80,
            MAG_GAIN_4_7 = 0xA0,
            MAG_GAIN_5_6 = 0xC0,
            MAG_GAIN_8_1 = 0xE0,
        } magGain_t;

    private:
        void write8(int reg, int val);
        int read8(int reg);
        void read();  
        void setGain(magGain_t gain);

        static const int MAG_ADDR = 0x1E;
        int _fd;

        int _x;
        int _y;
        int _z;
};
