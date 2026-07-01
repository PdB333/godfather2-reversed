// FUNC_NAME: CTransitionManager::update

#include <cstdint>

// Global data pointers (from game's static memory)
extern uint32_t g_pFadeOverlayTexture; // _DAT_00d5c458 - used in draw call
extern void* g_pGameManager;           // DAT_01223394 - Game manager instance

// Forward declarations for called functions
void FUN_0040c1f0(uint32_t color, uint32_t texture, int x, int y);
char FUN_0068c530(void); // Returns 0 if gameplay is active, else non-zero

// Known field offsets for CTransitionManager:
// +0x138: int32_t m_iRemainingTime   (fade timer countdown)
// +0x158: int32_t m_eFadeState       (0 = idle, 1 = ? , 2 = fade active)
// Known field offsets for game manager (singleton):
// +0x54:  bool   m_bGameplayAllowed  (non-zero allows actions)
// +0x58:  int32_t m_eGameState       (1 = main menu, other values = in game)

uint32_t __thiscall CTransitionManager::update(int this, char param_2)
{
    uint32_t texture = g_pFadeOverlayTexture;
    int remainingTime = *(int*)(this + 0x138);    // m_iRemainingTime
    int* pFadeState = (int*)(this + 0x158);       // m_eFadeState

    if (remainingTime < 1)
    {
        if (param_2 != '\0')
        {
            // Force fade: set state to 2 (fade active) and draw overlay
            *pFadeState = 2;
            FUN_0040c1f0(0xFF000000, texture, 0, 0); // Full-screen black overlay
            return 0; // Keep fading
        }

        // Check if fade can be skipped (only when state is 2 and game manager permits)
        if ((*pFadeState == 2) &&
            (*(bool*)((char*)g_pGameManager + 0x54) != false) &&  // m_bGameplayAllowed
            (*(int*)((char*)g_pGameManager + 0x58) != 1) &&       // Not main menu
            (FUN_0068c530() == '\0'))                             // Gameplay is active
        {
            return 0; // Keep fading (wait for next frame)
        }

        // No active fade or fade can be ended
        *pFadeState = 0; // Back to idle
    }

    return 1; // Fade completed or no fade running
}