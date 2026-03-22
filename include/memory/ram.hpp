#pragma once

#include <stdint.h>

namespace chip::Memory {

class RAM {
public:
    static void write(uint16_t address, uint8_t data);
    static uint8_t read(uint16_t address);
private:
    RAM() {}
    static uint8_t data_[4096];
};

}