#pragma once

#include <stdint.h>

namespace chip {

class Registers {
public:
    static void write(uint8_t address, uint8_t data);
    static uint8_t read(uint8_t address);
private:
    Registers() {}
    static uint8_t data_[16];
};

}