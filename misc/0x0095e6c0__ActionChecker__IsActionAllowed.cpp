// FUNC_NAME: ActionChecker::IsActionAllowed
// Function address: 0x0095e6c0
// Role: Determines if a specific action is allowed based on internal counters and global limits.
// The function reads various fields of the `this` object (size unknown) and compares them
// against static max values stored in global variables.

#include <cstdint>

// Forward declarations for external helpers
int GetCurrentTime();    // FUN_0095ca40 - likely returns some time/counter value
int GetMaxAllowedTime(); // FUN_0095ca80 - returns a limit for time-based action

// Action type enum matching param_2
enum ActionType : int {
    ACTION_COMBO       = 0,  // case 0
    ACTION_SPECIAL1    = 1,  // case 1
    ACTION_SPECIAL2    = 2,  // case 2
    ACTION_TIME_BASED  = 3,  // case 3 - uses external functions and a stored offset
    ACTION_AMMO        = 4,  // case 4
    ACTION_DODGE       = 5,  // case 5
    ACTION_HEALTH      = 6,  // case 6
    ACTION_ARMOR       = 7,  // case 7
    ACTION_FLAG        = 8,  // case 8 - reads a bool at offset +0x7A
    ACTION_ULTIMATE    = 9   // case 9
};

// Global limits (from DAT_011307ec etc.) - assumed extern
extern uint32_t g_maxComboCount;      // DAT_011307ec
extern uint32_t g_maxSpecial1Count;   // DAT_01130820
extern uint32_t g_maxSpecial2Count;   // DAT_011307fc
extern uint32_t g_maxAmmoCount;       // DAT_01130850
extern uint32_t g_maxDodgeCount;      // DAT_0113082c
extern uint32_t g_maxHealthCount;     // DAT_01130808
extern uint32_t g_maxArmorCount;      // DAT_01130814
extern uint32_t g_maxUltimateCount;   // DAT_01130844

class ActionChecker {
public:
    // Member fields (offsets from this):
    // +0x00: m_comboCount (int)
    // +0x04: padding?
    // +0x08: m_special2Count (int) [param_1[2]]
    // +0x0C: padding?
    // +0x10: ?
    // +0x14: m_healthCount (int) [param_1[5]]
    // +0x18: ?
    // +0x1C: m_ultimateCount (int) [param_1[7]]
    // +0x20: m_armorCount (int) [param_1[8]]
    // +0x24: m_ammoCount (int) [param_1[9]]
    // +0x28: m_dodgeCount (int) [param_1[10]]
    // +0x2C: ?
    // +0x30: ?
    // +0x34: m_timeBasedExtra (int) [param_1[0xd]]
    // +0x70: m_special1Count (int) [param_1[0x1c]]
    // +0x7A: m_actionFlag (bool/byte) [*(this+0x7a)]

    // Note: actual offsets might be larger due to class inheritance/vtable; this is a minimal layout

    bool IsActionAllowed(ActionType action) const;
};

bool ActionChecker::IsActionAllowed(ActionType action) const {
    switch(action) {
    case ACTION_COMBO:
        // Combo counter + 1 must be less than the global max combo count
        return (m_comboCount + 1U) < g_maxComboCount;

    case ACTION_SPECIAL1:
        // Special1 counter + 1 must be less than max
        return (m_special1Count + 1U) < g_maxSpecial1Count;

    case ACTION_SPECIAL2:
        // Special2 counter + 1 must be less than max
        return (m_special2Count + 1U) < g_maxSpecial2Count;

    case ACTION_TIME_BASED:
        // Time-based action: sum of current game time and stored extra offset must not exceed max allowed time
        {
            int currentTime = GetCurrentTime();   // iVar2
            int extra = m_timeBasedExtra;         // param_1[0xd]
            int maxAllowed = GetMaxAllowedTime(); // uVar3
            return (static_cast<uint32_t>(currentTime + extra) <= static_cast<uint32_t>(maxAllowed));
        }

    case ACTION_AMMO:
        // Ammo counter + 1 must be less than max ammo
        return (m_ammoCount + 1U) < g_maxAmmoCount;

    case ACTION_DODGE:
        // Dodge counter + 1 must be less than max dodge
        return (m_dodgeCount + 1U) < g_maxDodgeCount;

    case ACTION_HEALTH:
        // Health counter + 1 must be less than max health
        return (m_healthCount + 1U) < g_maxHealthCount;

    case ACTION_ARMOR:
        // Armor counter + 1 must be less than max armor
        return (m_armorCount + 1U) < g_maxArmorCount;

    case ACTION_FLAG:
        // Simple boolean flag at +0x7A determines permission
        return m_actionFlag;

    case ACTION_ULTIMATE:
        // Ultimate counter + 1 must be less than max ultimate
        return (m_ultimateCount + 1U) < g_maxUltimateCount;

    default:
        return false;
    }
}