#include "cpu/inst.hpp"
#include "io/video.hpp"
#include "io/input.hpp"
#include "timer/delay.hpp"
#include "timer/sound.hpp"
#include "memory/program.hpp"
#include "memory/stack.hpp"
#include "memory/registers.hpp"
#include "memory/index.hpp"
#include "memory/ram.hpp"

#include <cstdlib>

namespace chip {

void Inst::INST_00E0(uint16_t op) {
    static_cast<void>(op);
    chip::IO::Video::clear(0);
}

void Inst::INST_00EE(uint16_t op) {
    static_cast<void>(op);
    chip::Memory::Program::write(
        chip::Memory::Stack::pop()
    );
}

void Inst::INST_1nnn(uint16_t op) {
    uint16_t address = op & 0x0FFFu;
    chip::Memory::Program::write(address);
}

void Inst::INST_2nnn(uint16_t op) {
    uint16_t address = op & 0x0FFFu;
    chip::Memory::Stack::push(
        chip::Memory::Program::read()
    );
    chip::Memory::Program::write(address);
}

void Inst::INST_3xkk(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
	uint8_t byte = op & 0x00FFu;

	if (chip::Memory::Registers::read(Vx) == byte) {
        chip::Memory::Program::write(
            chip::Memory::Program::read() + 2
        );
    }
}

void Inst::INST_4xkk(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
	uint8_t byte = op & 0x00FFu;

	if (chip::Memory::Registers::read(Vx) != byte) {
        chip::Memory::Program::write(
            chip::Memory::Program::read() + 2
        );
    }
}

void Inst::INST_5xy0(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
    uint8_t Vy = (op & 0x00F0u) >> 4u;

    if (chip::Memory::Registers::read(Vx) == chip::Memory::Registers::read(Vy)) {
        chip::Memory::Program::write(chip::Memory::Program::read() + 2);
    }
}

void Inst::INST_6xkk(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
	uint8_t byte = op & 0x00FFu;

	chip::Memory::Registers::write(
        Vx,
        byte
    );
}

void Inst::INST_7xkk(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
	uint8_t byte = op & 0x00FFu;

	chip::Memory::Registers::write(
        Vx,
        chip::Memory::Registers::read(Vx) + byte
    );
}

void Inst::INST_8xy0(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
	uint8_t Vy = (op & 0x00F0u) >> 4u;

	chip::Memory::Registers::write(
        Vx,
        chip::Memory::Registers::read(Vy)
    );
}

void Inst::INST_8xy1(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
	uint8_t Vy = (op & 0x00F0u) >> 4u;

    chip::Memory::Registers::write(
        Vx,
        chip::Memory::Registers::read(Vx) | chip::Memory::Registers::read(Vy)
    );
}

void Inst::INST_8xy2(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
	uint8_t Vy = (op & 0x00F0u) >> 4u;

    chip::Memory::Registers::write(
        Vx,
        chip::Memory::Registers::read(Vx) & chip::Memory::Registers::read(Vy)
    );
}

void Inst::INST_8xy3(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
	uint8_t Vy = (op & 0x00F0u) >> 4u;

    chip::Memory::Registers::write(
        Vx,
        chip::Memory::Registers::read(Vx) ^ chip::Memory::Registers::read(Vy)
    );
}

void Inst::INST_8xy4(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
	uint8_t Vy = (op & 0x00F0u) >> 4u;

	uint16_t sum = chip::Memory::Registers::read(Vx) + chip::Memory::Registers::read(Vy);

	if (sum > 255U) {
		chip::Memory::Registers::write(0xF, 1);
	} else {
		chip::Memory::Registers::write(0xF, 0);
	}

    chip::Memory::Registers::write(Vx, sum & 0xFFu);
}

void Inst::INST_8xy5(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
	uint8_t Vy = (op & 0x00F0u) >> 4u;

	if (chip::Memory::Registers::read(Vx) >= chip::Memory::Registers::read(Vy)) {
		chip::Memory::Registers::write(0xF, 1);
	} else {
		chip::Memory::Registers::write(0xF, 0);
	}
    
    chip::Memory::Registers::write(
        Vx,
        chip::Memory::Registers::read(Vx) - chip::Memory::Registers::read(Vy)
    );
}

void Inst::INST_8xy6(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;

    uint8_t value = chip::Memory::Registers::read(Vx);

    chip::Memory::Registers::write(0xF, value & 0x01);
    chip::Memory::Registers::write(Vx, value >> 1);
}

void Inst::INST_8xy7(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
    uint8_t Vy = (op & 0x00F0u) >> 4u;

    uint8_t vx = chip::Memory::Registers::read(Vx);
    uint8_t vy = chip::Memory::Registers::read(Vy);

    if (vy >= vx) {
        chip::Memory::Registers::write(0xF, 1);
    } else {
        chip::Memory::Registers::write(0xF, 0);
    }

    chip::Memory::Registers::write(Vx, vy - vx);
}

void Inst::INST_8xyE(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;

    uint8_t value = chip::Memory::Registers::read(Vx);

    chip::Memory::Registers::write(0xF, (value & 0x80) >> 7);
    chip::Memory::Registers::write(Vx, value << 1);
}

void Inst::INST_9xy0(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
    uint8_t Vy = (op & 0x00F0u) >> 4u;

    if (chip::Memory::Registers::read(Vx) !=
        chip::Memory::Registers::read(Vy)) {
        chip::Memory::Program::write(
            chip::Memory::Program::read() + 2
        );
    }
}

void Inst::INST_Annn(uint16_t op) {
    uint16_t address = op & 0x0FFFu;
    chip::Memory::Index::write(address);
}

void Inst::INST_Bnnn(uint16_t op) {
    uint16_t address = op & 0x0FFFu;

    chip::Memory::Program::write(
        address + chip::Memory::Registers::read(0)
    );
}

void Inst::INST_Cxkk(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
    uint8_t byte = op & 0x00FFu;

    uint8_t rnd = rand() & 0xFF;

    chip::Memory::Registers::write(
        Vx,
        rnd & byte
    );
}

void Inst::INST_Dxyn(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
    uint8_t Vy = (op & 0x00F0u) >> 4u;
    uint8_t height = op & 0x000Fu;

    uint8_t  x = chip::Memory::Registers::read(Vx);
    uint8_t  y = chip::Memory::Registers::read(Vy);
    uint16_t i = chip::Memory::Index::read();

    chip::Memory::Registers::write(0xF, 0);

    for (int row = 0; row < height; row++) {
        uint8_t sprite = chip::Memory::RAM::read(i + row);

        for (int col = 0; col < 8; col++) {
            if ((sprite & (0x80 >> col)) != 0) {
                if (chip::IO::Video::xorPixel((x + col) % 64, (y + row) % 32)) {
                    chip::Memory::Registers::write(0xF, 1);
                }
            }
        }
    }
}

void Inst::INST_Ex9E(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
    uint8_t key = chip::Memory::Registers::read(Vx);

    if (chip::IO::Input::getKey(key)) {
        chip::Memory::Program::write(
            chip::Memory::Program::read() + 2
        );
    }
}

void Inst::INST_ExA1(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
    uint8_t key = chip::Memory::Registers::read(Vx);

    if (!chip::IO::Input::getKey(key)) {
        chip::Memory::Program::write(
            chip::Memory::Program::read() + 2
        );
    }
}

void Inst::INST_Fx07(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;

    chip::Memory::Registers::write(
        Vx,
        chip::Timer::Delay::get()
    );
}

void Inst::INST_Fx0A(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;

    int key = chip::IO::Input::getPressedKey();

    if (key == -1) {
        chip::Memory::Program::write(
            chip::Memory::Program::read() - 2
        );
    } else {
        chip::Memory::Registers::write(Vx, key);
    }
}

void Inst::INST_Fx15(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;

    chip::Timer::Delay::write(
        chip::Memory::Registers::read(Vx)
    );
}

void Inst::INST_Fx18(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;

    chip::Timer::Sound::write(
        chip::Memory::Registers::read(Vx)
    );
}

void Inst::INST_Fx1E(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;

    chip::Memory::Index::write(
        chip::Memory::Index::read() +
        chip::Memory::Registers::read(Vx)
    );
}

void Inst::INST_Fx29(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;

    chip::Memory::Index::write(
        chip::Memory::Registers::read(Vx) * 5
    );
}

void Inst::INST_Fx33(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
    uint8_t value = chip::Memory::Registers::read(Vx);
    uint16_t i = chip::Memory::Index::read();

    chip::Memory::RAM::write(i,     (value / 100)     );
    chip::Memory::RAM::write(i + 1, (value / 10 ) % 10);
    chip::Memory::RAM::write(i + 2, (value % 10 )     );
}

void Inst::INST_Fx55(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
    uint16_t i = chip::Memory::Index::read();

    for (int r = 0; r <= Vx; r++) {
        chip::Memory::RAM::write(
            i + r,
            chip::Memory::Registers::read(r)
        );
    }

    chip::Memory::Index::write(i + Vx + 1);
}

void Inst::INST_Fx65(uint16_t op) {
    uint8_t Vx = (op & 0x0F00u) >> 8u;
    uint16_t i = chip::Memory::Index::read();

    for (int r = 0; r <= Vx; r++) {
        chip::Memory::Registers::write(
            r,
            chip::Memory::RAM::read(i + r)
        );
    }

    chip::Memory::Index::write(i + Vx + 1);
}

}