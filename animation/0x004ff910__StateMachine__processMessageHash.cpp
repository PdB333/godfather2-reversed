// FUNC_NAME: StateMachine::processMessageHash
void __thiscall StateMachine::processMessageHash(StateMachine* this, uint32_t messageHash) {
    if (messageHash == 0x26ba025e) {
        // Message identified as "activate" or similar: set bit1, clear bit2 in flags
        *(uint32_t*)((uint8_t*)this + 0x3c) = (*(uint32_t*)((uint8_t*)this + 0x3c) & 0xfffffffb) | 2;
    } else if (messageHash == 0x79c328b9) {
        // Message identified as "start" or similar
        uint32_t local_20[4] = {0, 0, 0, 0};  // 16-byte zeroed structure
        if (*(int32_t*)((uint8_t*)this + 0x28) != 0) {
            // If a specific pointer exists, clear the structure and return (substate active?)
            FUN_004e94a0(local_20, 0);
            return;
        }
        // Otherwise set bit3 in flags
        *(uint32_t*)((uint8_t*)this + 0x3c) = *(uint32_t*)((uint8_t*)this + 0x3c) | 8;
    } else if (messageHash == 0x8A1C9390) { // Equivalent to -0x75e36c70
        // Message identified as "deactivate" or similar: set bit2, clear bit1 in flags
        *(uint32_t*)((uint8_t*)this + 0x3c) = (*(uint32_t*)((uint8_t*)this + 0x3c) & 0xfffffffd) | 4;
    }
}