#include "memory/stack.hpp"

namespace chip::Memory {

uint16_t Stack::data_[16] = {0x0000};
uint8_t Stack::sp_ = 0x00;

void Stack::push(uint16_t value) {
    if (sp_ >= 16) return;
    data_[sp_] = value;
    sp_++;
}

uint16_t Stack::pop() {
    if (sp_ == 0) return 0x0000;
    sp_--;
    return data_[sp_];
}

}