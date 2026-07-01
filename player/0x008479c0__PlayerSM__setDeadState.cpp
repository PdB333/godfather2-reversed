// FUNC_NAME: PlayerSM::setDeadState
void __thiscall PlayerSM::setDeadState(PlayerSM* this, void* param2, int alive) {
    if (alive != 1) {
        return;
    }

    // Clear bits 9-10? (0x180 = bit 7 and 8), mask 0xfffff9ff clears bits 9 and 10 (since 0x600 masks out)
    // Actually: 0x180 = bits 7,8 ; 0xfffff9ff = ~0x600? Wait: 0xfffff9ff = 1111 1111 1111 1111 1111 1001 1111 1111
    // That clears bits 9 and 10? Let's compute: 0x600 = 0000 0110 0000 0000? No. 0x600 = 0b0000 0110 0000 0000 -> bits 9 and 10 (since bit0 is LSB)
    // Actually 0x180 = 0b0000 0001 1000 0000 -> bits 7 and 8.
    // 0xfffff9ff = 0b1111 1111 1111 1111 1111 1001 1111 1111 -> clears bit 9 and bit 10? No: bit 9 is 0x200, bit 10 is 0x400, that would be 0x600 mask. 0xfffff9ff inverted = 0x600? Let's verify: 0xfffff9ff bitwise NOT = 0x00000600, yes clears bits 9 and 10.
    // Then sets 0x180 (bits 7 and 8). So it sets bits 7,8 and clears bits 9,10?
    // That seems like a state transition from some state to another.
    uint flags = *(uint*)(this + 0x118);
    flags = (flags & 0xfffff9ff) | 0x180;
    *(uint*)(this + 0x118) = flags;

    // Call some logging or event handler (maybe debug print)
    FUN_004b1960(&LAB_00843160); // likely a string constant

    // If bit 4 (0x10) is set in the flags, call another function
    if ((*(byte*)(this + 0x118) & 0x10) != 0) {
        FUN_008473d0(0, 0);
    }
}