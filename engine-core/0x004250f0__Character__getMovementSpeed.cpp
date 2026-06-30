// FUNC_NAME: Character::getMovementSpeed

float Character::getMovementSpeed(void* animContext) {
    // +0xe4 is a flag for overriding speed (likely boolean)
    if (*(bool*)(this + 0xe4)) {
        // +0x148 holds the custom speed override, multiplied by global game speed factor
        return *(float*)(this + 0x148) * g_gameSpeed; // DAT_00e445c8
    }

    // Get current animation state index from the animation context
    int stateIndex = getCurrentAnimIndex(animContext); // FUN_00424c90

    // +0x10 is a pointer to an array of movement-related data structures (size 0x1d0 each)
    // At offset 0x30 within each structure we have the actual speed for that state
    return *(float*)(*(int*)(this + 0x10) + stateIndex * 0x1d0 + 0x30);
}