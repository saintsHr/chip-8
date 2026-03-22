#include "io/sound.hpp"

#include <cmath>

namespace chip::IO {

bool Sound::playing_ = false;

void Sound::audioCallback(void* userdata, Uint8* stream, int len) {
    static_cast<void>(userdata);

    static double phase = 0.0;
    Sint16* buffer = (Sint16*)stream;
    int length = len / 2;

    for (int i = 0; i < length; ++i) {
        if (playing_) {
            buffer[i] = AMPLITUDE * (std::sin(phase) > 0 ? 1 : -1);
        } else {
            buffer[i] = 0;
        }

        phase += 2.0 * M_PI * FREQUENCY / SAMPLE_RATE;
        if (phase > 2.0 * M_PI) phase -= 2.0 * M_PI;
    }
}

void Sound::init() {
    SDL_Init(SDL_INIT_AUDIO);

    SDL_AudioSpec spec;
    spec.freq = SAMPLE_RATE;
    spec.format = AUDIO_S16SYS;
    spec.channels = 1;
    spec.samples = 1024;
    spec.callback = audioCallback;
    spec.userdata = nullptr;

    if (SDL_OpenAudio(&spec, nullptr) < 0) return;

    SDL_PauseAudio(0);
}

}