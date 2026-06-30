// FUNC_NAME: GodfatherGameManager::initializeGameState
// Address: 0x0068c7a0
// Role: Initializes the game state member fields and global variables for a new game mode or scenario.
void __fastcall GodfatherGameManager::initializeGameState(int thisPtr)
{
    // Set the state byte (probably a current phase/step) to 18 (0x12)
    *(uint8_t*)(thisPtr + 0x14) = 0x12;

    // Clear a 32-bit counter or timer field at offset 0x18
    *(int32_t*)(thisPtr + 0x18) = 0;

    // Set global game mode indicator to 17 (0x11)
    g_globalGameMode = 0x11;

    // Write to a global structure at offset +0xC (likely a manager or system field)
    *(int32_t*)(g_globalManagerPtr + 0xC) = 5;

    // Call a supporting initialization subroutine
    sub_5648C0();

    // If the state at offset 0x10 is not 3, reset it to 0
    if (*(int32_t*)(thisPtr + 0x10) != 3)
    {
        *(int32_t*)(thisPtr + 0x10) = 0;
    }
}