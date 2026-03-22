#pragma once

#include <SDL2/SDL.h>

#define SAMPLE_RATE 44100
#define AMPLITUDE   4000
#define FREQUENCY   440

namespace chip::IO {

class Sound {
public:
    static void init();
    static void play() { playing_ = true; }
    static void stop() { playing_ = false; }
private:
    Sound();
    static bool playing_;
    static void audioCallback(void* userdata, Uint8* stream, int len);
};

}