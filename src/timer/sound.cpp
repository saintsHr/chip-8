#include "timer/sound.hpp"

namespace chip::Timer {

uint16_t Sound::data_ = 0x0000;

void Sound::write(uint16_t data) {
    data_ = data;
}

void Sound::step() {
    if (data_ > 0x0000) data_--;
}

}