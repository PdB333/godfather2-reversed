// FUNC_NAME: GodfatherGameManager::getCurrentPlayerHandle
// Address: 0x004e3a50
// Returns a handle to the current player entity (or fallback) from the global game manager singleton.
// The global g_pGameManager (DAT_012054dc) is a pointer to the GodfatherGameManager instance.
// Offset +0x170 likely stores the active player's entity handle/ID.
// If the manager is null, returns a fallback handle from g_fallbackPlayerHandle (DAT_012058a8).

extern void* g_pGameManager;            // DAT_012054dc
extern int   g_fallbackPlayerHandle;    // DAT_012058a8

class GodfatherGameManager {
public:
    static int getCurrentPlayerHandle();
};

int GodfatherGameManager::getCurrentPlayerHandle() {
    if (g_pGameManager != nullptr) {
        return *(int*)((char*)g_pGameManager + 0x170); // +0x170: player handle
    }
    return g_fallbackPlayerHandle;
}