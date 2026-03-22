#include "common.hpp"

#include <SDL2/SDL.h>
#include <random>
#include <iostream>
#include <fstream>

#define PIXEL_SIZE 16

uint8_t fontset[80] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

uint8_t randomByte() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, 255);
    return static_cast<uint8_t>(dist(gen));
}

bool loadROM(char const* filename) {
	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if (file.is_open()) {
		std::streampos size = file.tellg();
		char* buffer = new char[size];

		file.seekg(0, std::ios::beg);
		file.read(buffer, size);
		file.close();

		for (long i = 0; i < size; ++i) {
            chip::Memory::RAM::write(0x200 + i, buffer[i]);
		}

		delete[] buffer;
	} else {
        std::cout << "\ncannot open rom\n" << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "\nusage: ./chip-8 <rom>\n" << std::endl;
        return 1;
    }

    // --- inits SDL2 ---
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

    // --- creates window ---
        SDL_Window* window = SDL_CreateWindow(
        "CHIP-8",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        64 * PIXEL_SIZE,
        32 * PIXEL_SIZE,
        0
    );

    // --- inits renderer ---
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    // --- inits sound ---
    chip::IO::Sound::init();

    // --- loads fontset ---
    for (unsigned int i = 0; i < 0x50; ++i) {
        chip::Memory::RAM::write(0x50 + i, fontset[i]);
	}

    // --- loads rom ---
    if (!loadROM(argv[1])) return 1;

    // --- main loop ---
    bool running = true;
    SDL_Event event;

    while (running) {
        // --- poll events ---
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        // --- clears the window
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // --- render framebuffer ---
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int y = 0; y < 32; ++y) {
            for (int x = 0; x < 64; ++x) {
                if (chip::IO::Video::getPixel(x, y)) {
                    SDL_Rect r = { x * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE };
                    SDL_RenderFillRect(renderer, &r);
                }
            }
        }

        // --- steps timers ---
        chip::Timer::Delay::step();
        chip::Timer::Sound::step();

        // --- presents ---
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return 0;
}