#include "memory/program.hpp"

namespace chip {

uint16_t Program::data_ = 0x0000;

void Program::write(uint16_t data) {
    data_ = data;
}

uint16_t Program::read() {
    return data_;
}

}