// FUNC_NAME: NPC::shouldTriggerAction
// Address: 0x00723570
// This function determines whether an NPC should react to some event (e.g., taking damage, noticing player).
// It uses a two‑layer chance check: first a global random seed vs. a per‑NPC threshold,
// then (if not forced) a secondary roll that incorporates the player’s luck stat.
// param_2 acts as a “force override” that bypasses the secondary random check.

#include <cstdlib>

// Global random threshold (likely updated each frame)
extern float g_randomThreshold; // DAT_00e44598

// Global multiplier for the secondary chance roll
extern float g_luckScaleFactor; // DAT_00e44590

// Global manager pointer; +0x04 holds a pointer to the current player object
extern uint32_t* g_playerManager; // DAT_012233a0

// Invalid sentinel value used to check if the player pointer is valid
const uint32_t kInvalidPlayerHandle = 0x1f30;

// The function is a __thiscall member of an NPC class.
// Offsets:
//   +0x13c: m_chanceThreshold    (float)  – base probability for the first random check
//   +0x140: m_probabilityFactor  (float)  – multiplier for the player’s luck in the secondary roll
bool __thiscall NPC::shouldTriggerAction(void* thisPtr, char forceOverride)
{
    // First chance: compare global random seed to NPC's threshold
    if (g_randomThreshold < *(float*)((uint8_t*)thisPtr + 0x13c))
    {
        // Either forced, or pass a second chance roll
        if (forceOverride != '\0')
        {
            return true;
        }

        // Retrieve player object pointer from the global manager
        uint32_t* playerData = *(uint32_t**)(g_playerManager + 1); // g_playerManager+4 => pointer to player
        if (playerData != nullptr && playerData != (uint32_t*)kInvalidPlayerHandle)
        {
            float playerLuck = *(float*)(playerData + 0x7e); // +0x1f8 => luck stat (offset = 0x1f8/4 = 126 = 0x7e)
            float threshold = *(float*)((uint8_t*)thisPtr + 0x140); // m_probabilityFactor
            int randomVal = std::rand();
            // Random roll: (rand() * g_luckScaleFactor) < (m_probabilityFactor * playerLuck)
            if ((float)randomVal * g_luckScaleFactor < threshold * playerLuck)
            {
                return true;
            }
        }
    }

    return false;
}