// FUNC_NAME: GodfatherGameManager::isGameActive

#include <cstdint>

// Global singleton instance of GodfatherGameManager (likely from some Singleton pattern)
extern void* g_pGodfatherGameManager; // at 0x0112aa1c? Actually DAT_0112aa1c is a pointer to the singleton, so treat as a global variable

// Forward declarations of called functions
int __cdecl getGameState(); // FUN_00806440 - returns current game state (0,1,2,...)
bool __cdecl isDialogUIActive(); // FUN_00784770 - checks if some dialog/UI is active

bool GodfatherGameManager::isGameActive()
{
    int gameState = getGameState();
    if (gameState == 2)
    {
        // Offset +0x2C6c: likely a flags bitfield; check bit 7 (0x80)
        uint32_t* flags = (uint32_t*)((uint8_t*)g_pGodfatherGameManager + 0x2C6c);
        if (*flags & 0x80)
        {
            return true;
        }

        // Offset +0x2C88: pointer to some active UI/dialog object
        void* activeDialog = *(void**)((uint8_t*)g_pGodfatherGameManager + 0x2C88);
        if (activeDialog != nullptr && isDialogUIActive())
        {
            return true;
        }
    }
    return false;
}