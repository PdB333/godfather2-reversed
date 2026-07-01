// FUNC_NAME: GodfatherGameManager::updatePauseState
void __fastcall GodfatherGameManager::updatePauseState(void* this)
{
    // Access internal state pointer at offset +0x5c
    void* statePtr = *(void**)((char*)this + 0x5c);
    // Check if a specific flag is set (bit 14 at +0x8e4) and a pointer at +0x21dc is non-null
    if (*(int*)((char*)statePtr + 0x21dc) != 0 &&
        (*(unsigned int*)((char*)statePtr + 0x8e4) >> 0xe & 1) != 0)
    {
        // Pause/menu active, run paused update
        handlePausedUpdate();
        return;
    }
    // Normal game update
    handleNormalUpdate();
}