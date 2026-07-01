// FUNC_NAME: PlayerSM::getActiveSubState
int __thiscall PlayerSM::getActiveSubState(int context) {
    // context is pointer to a PlayerContext or input state with flags at offset 0x2C
    // Bit 1 (0x2) indicates cover state active
    if (*(uint32_t*)(context + 0x2C) & 2) {
        // Return pointer to cover state sub-object (offset 0x120)
        return (int)this + 0x120;
    } else {
        // Return pointer to ground state sub-object (offset 0x130)
        return (int)this + 0x130;
    }
}