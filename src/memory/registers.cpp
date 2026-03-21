#include "memory/registers.hpp"

namespace chip {

uint8_t Registers::data_[16] = {0x00};

void Registers::write(uint8_t address, uint8_t data) {
    if (address > 0xF) return;
    data_[address] = data;
}

uint8_t Registers::read(uint8_t address) {
    if (address > 0xF) return 0x00;
    return data_[address];
}

}