// FUNC_NAME: InputManager::applyInputMasks
void __thiscall InputManager::applyInputMasks(uint* outputFlags) // param_2 = outputFlags (pointer to input state)
{
    uint clearMask = *(uint*)(this + 0x88); // +0x88: clear flags (bits to clear in output)
    uint setMask   = *(uint*)(this + 0x8C); // +0x8C: set flags (bits to set in output)

    // --- Apply clear operations ---
    if ((clearMask & 1) != 0) {
        handleClearBit1(); // FUN_006b5ac0 - action when clearing bit 1
    }
    if ((clearMask & 4) != 0) {
        handleClearBit4(0); // FUN_006b2600(0) - action when clearing bit 4
    }
    if ((clearMask & 0x10) != 0) {
        outputFlags[0x34] &= ~0x10; // +0x34: clear bit 4 (input flag)
    }
    if ((clearMask & 0x20) != 0) {
        outputFlags[0x34] &= ~0x20;
    }
    if ((clearMask & 0x40) != 0) {
        outputFlags[0x34] &= ~0x40;
    }
    if ((clearMask & 0x80) != 0) { // (char)uVar1 < 0 => bit 7
        outputFlags[0x34] &= ~0x80;
    }
    if ((clearMask & 0x100) != 0) {
        outputFlags[0x34] &= ~0x100;
    }
    if ((clearMask & 0x200) != 0) {
        outputFlags[0x34] &= ~0x200;
    }
    if ((clearMask & 0x400) != 0) {
        outputFlags[0x34] &= ~0x400;
    }
    if ((clearMask & 0x800) != 0) {
        outputFlags[0x34] &= ~0x800;
    }
    if ((clearMask & 8) != 0) {
        outputFlags[0x34] &= ~8;
    }

    // --- Apply set operations ---
    if ((setMask & 1) != 0) {
        handleSetBit1(); // FUN_006b5b10 - action when setting bit 1
    }
    if ((setMask & 4) != 0) {
        handleSetBit4(1); // FUN_006b2600(1) - action when setting bit 4
    }
    if ((setMask & 0x10) != 0) {
        outputFlags[0x34] |= 0x10;
    }
    if ((setMask & 0x20) != 0) {
        outputFlags[0x34] |= 0x20;
    }
    if ((setMask & 0x40) != 0) {
        outputFlags[0x34] |= 0x40;
    }
    if ((setMask & 0x80) != 0) {
        outputFlags[0x34] |= 0x80;
    }
    if ((setMask & 0x100) != 0) {
        outputFlags[0x34] |= 0x100;
    }
    if ((setMask & 0x200) != 0) {
        outputFlags[0x34] |= 0x200;
    }
    if ((setMask & 0x400) != 0) {
        outputFlags[0x34] |= 0x400;
    }
    if ((setMask & 0x800) != 0) {
        outputFlags[0x34] |= 0x800;
    }
    if ((setMask & 8) != 0) {
        outputFlags[0x34] |= 8;
    }
}