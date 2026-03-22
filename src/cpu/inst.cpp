#include "cpu/inst.hpp"
#include "io/video.hpp"
#include "memory/program.hpp"
#include "memory/stack.hpp"
#include "memory/registers.hpp"

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
	uint8_t Vy = (op & 0x0F00u) >> 4u;

	if (chip::Memory::Registers::read(Vx) == chip::Memory::Registers::read(Vx)) {
        chip::Memory::Program::write(
            chip::Memory::Program::read() + 2
        );
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
        chip::Memory::Registers::read(Vx) + 2
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

	if (chip::Memory::Registers::read(Vx) > chip::Memory::Registers::read(Vy)) {
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
    
}

void Inst::INST_8xy7(uint16_t op) {
    
}

void Inst::INST_8xyE(uint16_t op) {
    
}

void Inst::INST_9xy0(uint16_t op) {
    
}

void Inst::INST_Annn(uint16_t op) {
    
}

void Inst::INST_Bnnn(uint16_t op) {
    
}

void Inst::INST_Cxkk(uint16_t op) {
    
}

void Inst::INST_Dxyn(uint16_t op) {
    
}

void Inst::INST_Ex9E(uint16_t op) {
    
}

void Inst::INST_ExA1(uint16_t op) {
    
}

void Inst::INST_Fx07(uint16_t op) {
    
}

void Inst::INST_Fx0A(uint16_t op) {
    
}

void Inst::INST_Fx15(uint16_t op) {
    
}

void Inst::INST_Fx18(uint16_t op) {
    
}

void Inst::INST_Fx1E(uint16_t op) {
    
}

void Inst::INST_Fx29(uint16_t op) {
    
}

void Inst::INST_Fx33(uint16_t op) {
    
}

void Inst::INST_Fx55(uint16_t op) {
    
}

void Inst::INST_Fx65(uint16_t op) {
    
}

}