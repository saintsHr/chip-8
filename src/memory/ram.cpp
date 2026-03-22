#include "memory/ram.hpp"

namespace chip::Memory {

uint8_t RAM::data_[4096] = {0x00};

void RAM::write(uint16_t address, uint8_t data) {
    if (address > 0xFFF) return;
    data_[address] = data;
}

uint8_t RAM::read(uint16_t address) {
    if (address > 0xFFF) return 0x00;
    return data_[address];
}

}