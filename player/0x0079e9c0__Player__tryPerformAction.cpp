// FUNC_NAME: Player::tryPerformAction

bool __thiscall Player::tryPerformAction(void* thisPtr, int param_2) {
    bool result = false;
    // Check bit 1 of action flags at offset 0x249c
    uint32_t actionFlags = *(uint32_t*)((uint8_t*)thisPtr + 0x249c);
    if ((actionFlags >> 1) & 1) {
        // Global condition check (e.g., is game active, player alive)
        if (FUN_00481620() != 0) {
            result = true;
            // Start the action with the action type byte at +0x2498 and the given parameter
            FUN_004654d0(*(uint8_t*)((uint8_t*)thisPtr + 0x2498), param_2);
        }
    }
    return result;
}