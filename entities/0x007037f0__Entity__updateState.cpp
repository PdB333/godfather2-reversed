// FUNC_NAME: Entity::updateState
// This function appears to be the main update for an entity, choosing between two behavior paths
// based on the presence of a controller sub-object (m_pController at +0x328).
// It also checks a flag at +0x2d8 bit 2 to conditionally call additional update functions.

#include <cstdint>

class Entity {
public:
    // Offsets (relative to 'this'):
    // +0x214: m_entityType (int32_t) - entity type identifier, 0x48 (72) is a special type to skip
    // +0x328: m_pController (void*) - pointer to a controller object (e.g., AI controller, player input)
    // +0x2d8: m_flags (uint32_t) - bitfield with flags, bit 2 = FLAG_UPDATE_EXTRA
    int32_t m_entityType;          // +0x214
    void* m_pController;           // +0x328
    uint32_t m_flags;              // +0x2d8
};

// Forward declarations of callees (renamed for clarity)
bool isActionableState();                                              // FUN_00701ed0
void updateActionable();                                              // FUN_00701f40
void updateWithController();                                          // FUN_00702fc0
void updateAIOrPlayer();                                              // FUN_00709120
void updateCombat();                                                  // FUN_007029f0
void updateDebugVisuals();                                            // FUN_007079a0
void updateEffects();                                                 // FUN_0079ce10

void __fastcall Entity::updateState(Entity* this)
{
    // Only update if entity type is valid and not a special "skip" type (0x48)
    if (this->m_entityType != 0 && this->m_entityType != 0x48)
    {
        if (this->m_pController == nullptr)
        {
            // No controller: check if entity is in an actionable state
            if ((this->m_flags >> 2 & 1) == 0)  // bit 2 not set
            {
                bool actionable = isActionableState();
                if (actionable)
                {
                    updateActionable();
                }
            }
            // If bit 2 is set, we skip the actionable branch (possibly already handled)
        }
        else
        {
            // Has a controller: use the full controller-driven update
            updateWithController();
            updateAIOrPlayer();
            if ((this->m_flags >> 2 & 1) != 0)  // bit 2 set
            {
                updateCombat();
            }
        }

        // Common extra updates when bit 2 is set (e.g., debug, effects)
        if ((this->m_flags >> 2 & 1) != 0)
        {
            updateDebugVisuals();
            updateEffects();
        }
    }
}