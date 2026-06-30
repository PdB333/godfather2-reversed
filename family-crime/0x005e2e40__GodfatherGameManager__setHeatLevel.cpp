// FUNC_NAME: GodfatherGameManager::setHeatLevel
#include <cstdint>

// Global singleton pointer to the game manager (DAT_0122350c)
extern GodfatherGameManager* g_pGameManager;

/**
 * @brief Sets the player's heat level, clamping to a maximum of 5.
 * 
 * The heat level controls police attention and notoriety. Valid range is 0–5.
 * 
 * @param level Desired heat level; if >5, clamped to 5.
 */
void GodfatherGameManager::setHeatLevel(uint32_t level)
{
    const uint32_t kMaxHeatLevel = 5;

    // +0x174c: heatLevel field in singleton instance
    uint32_t* pHeatLevel = reinterpret_cast<uint32_t*>(
        reinterpret_cast<char*>(g_pGameManager) + 0x174c
    );

    if (level > kMaxHeatLevel) {
        *pHeatLevel = kMaxHeatLevel;
    } else {
        *pHeatLevel = level;
    }
}