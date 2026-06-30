// FUNC_NAME: GodfatherGameManager::setForceUpdate
void __fastcall GodfatherGameManager::setForceUpdate(GodfatherGameManager* this) {
    // Set a flag at offset 0x8048 to signal a forced update (e.g., for game state sync)
    *(uint8_t*)((uintptr_t)this + 0x8048) = 1;
}