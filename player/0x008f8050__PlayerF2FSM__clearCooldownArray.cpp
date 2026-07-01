// FUNC_NAME: PlayerF2FSM::clearCooldownArray
// Function at 0x008f8050 zeros an array of 52 ints/floats at offset +0x208 to +0x2d8.
// This is likely a cooldown or timer array for player state machine (e.g., abilities, transitions).
void __thiscall PlayerF2FSM::clearCooldownArray(PlayerF2FSM* this) {
    // Zero 52 elements, each 4 bytes, starting at this+0x208
    for (int i = 0; i < 52; i++) {
        *(uint32_t*)((char*)this + 0x208 + i * 4) = 0;
    }
}