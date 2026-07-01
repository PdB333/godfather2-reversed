// FUNC_NAME: Player::resetState
void __thiscall Player::resetState(int thisPtr) {
    // Call base class initialization (likely BaseEntity::reset)
    BaseEntity::reset();
    
    // Clear pointer to active action state machine (e.g., combat state)
    *(int*)(thisPtr + 0x58) = 0;
    // Clear pointer to behavior timer or cooldown
    *(int*)(thisPtr + 0x74) = 0;
    // Reset boolean flags: e.g., isInCover, isAiming
    *(bool*)(thisPtr + 0xa0) = false;
    *(bool*)(thisPtr + 0xa1) = false;
    
    // Free and null out a dynamically allocated sub-object (e.g., inventory, weapon)
    if (*(int*)(thisPtr + 0xa4) != 0) {
        MemoryManager::freeObject((void**)(thisPtr + 0xa4));
        *(int*)(thisPtr + 0xa4) = 0;
    }
}