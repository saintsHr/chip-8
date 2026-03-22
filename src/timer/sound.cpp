#include "timer/sound.hpp"
#include "io/sound.hpp"

namespace chip::Timer {

uint8_t Sound::data_ = 0x00;

void Sound::write(uint8_t data) {
    data_ = data;
}

void Sound::step() {
    if (data_ > 0x00) {
        chip::IO::Sound::play();
        data_--;
    } else {
        chip::IO::Sound::stop();
    }
}

}