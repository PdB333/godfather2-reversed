// FUNC_NAME: CharacterManager::initializeSlots
void CharacterManager::initializeSlots(void* thisPtr, int param2) {
    // First group: indices 0x26-0x29 (4 slots, likely special characters)
    for (uint index = 0x26; index < 0x2a; index++) {
        FUN_0049ab20(thisPtr, param2, index);
    }
    // Second group: indices 0-0x0F (16 slots, likely player characters)
    for (uint index = 0; index < 0x10; index++) {
        FUN_0049ab20(thisPtr, param2, index);
    }
    // Third group: indices 0x15-0x24 (16 slots, likely enemy/NPC types)
    for (uint index = 0x15; index < 0x25; index++) {
        FUN_0049ab20(thisPtr, param2, index);
    }
}