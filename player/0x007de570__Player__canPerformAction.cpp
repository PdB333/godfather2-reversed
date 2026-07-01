// FUNC_NAME: Player::canPerformAction
// Function address: 0x007de570
// Checks if the player is allowed to perform a specific action (e.g., enter cover or interact) based on:
//   - Player state flags at characterData +0x8E4 (bits 9 and 16 must be clear)
//   - Global input manager state (byte at +4, bit 2 must be set)
//   - Global game state manager state (byte at +4, bit 2 must be set)

bool __thiscall Player::canPerformAction(void)
{
    // Pointer to character data stored at Player +0x58
    void* characterData = *(void**)((char*)this + 0x58);

    // Read player status flags from characterData +0x8E4
    uint flags = *(uint*)((char*)characterData + 0x8E4);

    // Check that bit 16 (0x10000) and bit 9 (0x200) are both zero
    if ( ((flags >> 16) & 1) == 0 && ((flags >> 9) & 1) == 0 )
    {
        // Get global input manager (likely a singleton)
        void* inputMgr = getInputManager(); // originally FUN_007ab130

        // Verify that input processing is enabled; bit 2 (= 4) of byte at inputMgr + 4
        if ( (*(byte*)((char*)inputMgr + 4) & 4) != 0 )
        {
            // Get global game state manager (likely another singleton)
            void* gameStateMgr = getGameStateManager(); // originally FUN_007ab160

            // Verify that game state allows the action; same bit layout
            if ( (*(byte*)((char*)gameStateMgr + 4) & 4) != 0 )
            {
                return true;
            }
        }
    }
    return false;
}