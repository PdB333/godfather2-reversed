// FUNC_NAME: GodfatherGameManager::isInputLockedOrPaused
uint GodfatherGameManager::isInputLockedOrPaused(void) {
    int iVar1;
    uint uVar2;

    // Get singleton pointer to the main game manager (likely GodfatherGameManager)
    iVar1 = FUN_009b2910(); // e.g., getGodfatherGameManager()
    if (iVar1 == 0) {
        uVar2 = 1; // No manager -> assume input locked
    } else {
        uVar2 = FUN_009b24b0(); // e.g., getInputFlags() - returns current input state flags
        // Check if input flags are non-zero (char conversion checks low byte)
        // AND the bit at offset 0x8E8 (bit 28 of a 4-byte field) is set
        // (likely a flag indicating a menu or cutscene is active)
        if (((char)uVar2 != '\0') && (((byte)((uint)*(undefined4 *)(iVar1 + 0x8e8) >> 0x1c) & 1) != 0))
        {
            // If both conditions true, clear the low byte of the flags (e.g., mask out action ID)
            return uVar2 & 0xffffff00;
        }
    }
    return uVar2; // Otherwise return raw flags (including low byte)
}