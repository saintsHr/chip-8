#include "memory/index.hpp"

namespace chip {

uint16_t Index::data_ = 0x0000;

void Index::write(uint16_t data) {
    data_ = data;
}

uint16_t Index::read() {
    return data_;
}

}