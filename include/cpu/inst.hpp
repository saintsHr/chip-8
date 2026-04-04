#pragma once

#include <cstdint>

namespace chip {

class Inst {
public:
    static void INST_00E0(uint16_t op); // CLS   (Clears display)
    static void INST_00EE(uint16_t op); // RET   (Returns from subroutine)
    static void INST_1nnn(uint16_t op); // JMP   (Jump to address nnn)
    static void INST_2nnn(uint16_t op); // CALL  (Call subroutine at nnn)
    static void INST_3xkk(uint16_t op); // SE    (Skip next inst if Vx == kk)
    static void INST_4xkk(uint16_t op); // SNE   (Skip next inst if Vx != kk)
    static void INST_5xy0(uint16_t op); // SE    (Skip next inst if Vx == Vy)
    static void INST_6xkk(uint16_t op); // LD    (Set Vx = kk)
    static void INST_7xkk(uint16_t op); // ADD   (Set Vx = Vx + kk)
    static void INST_8xy0(uint16_t op); // LD    (Set Vx = Vy)
    static void INST_8xy1(uint16_t op); // OR    (Set Vx = Vx OR Vy)
    static void INST_8xy2(uint16_t op); // AND   (Set Vx = Vx AND Vy)
    static void INST_8xy3(uint16_t op); // XOR   (Set Vx = Vx XOR Vy)
    static void INST_8xy4(uint16_t op); // ADD   (Set Vx = Vx + Vy, VF = carry)
    static void INST_8xy5(uint16_t op); // SUB   (Set Vx = Vx - Vy, VF = NOT borrow)
    static void INST_8xy6(uint16_t op); // SHR   (Shift Vx right by 1, VF = LSB)
    static void INST_8xy7(uint16_t op); // SUBN  (Set Vx = Vy - Vx, VF = NOT borrow)
    static void INST_8xyE(uint16_t op); // SHL   (Shift Vx left by 1, VF = MSB)
    static void INST_9xy0(uint16_t op); // SNE   (Skip next inst if Vx != Vy)
    static void INST_Annn(uint16_t op); // LD    (Set I = nnn)
    static void INST_Bnnn(uint16_t op); // JP V0 (Jump to nnn + V0)
    static void INST_Cxkk(uint16_t op); // RND   (Set Vx = random byte AND kk)
    static void INST_Dxyn(uint16_t op); // DRW   (Draw sprite at (Vx, Vy), height n)
    static void INST_Ex9E(uint16_t op); // SKP   (Skip next inst if key in Vx is pressed)
    static void INST_ExA1(uint16_t op); // SKNP  (Skip next inst if key in Vx is NOT pressed)
    static void INST_Fx07(uint16_t op); // LD    (Set Vx = delay timer)
    static void INST_Fx0A(uint16_t op); // LD    (Wait for key press, store in Vx)
    static void INST_Fx15(uint16_t op); // LD    (Set delay timer = Vx)
    static void INST_Fx18(uint16_t op); // LD    (Set sound timer = Vx)
    static void INST_Fx1E(uint16_t op); // ADD   (Set I = I + Vx)
    static void INST_Fx29(uint16_t op); // LD    (Set I = location of sprite for digit Vx)
    static void INST_Fx33(uint16_t op); // BCD   (Store BCD of Vx in memory I, I+1, I+2)
    static void INST_Fx55(uint16_t op); // LD    (Store V0..Vx in memory starting at I)
    static void INST_Fx65(uint16_t op); // LD    (Read V0..Vx from memory starting at I)
private:
    Inst() {}
};

}