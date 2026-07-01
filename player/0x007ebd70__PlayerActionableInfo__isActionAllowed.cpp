// FUNC_NAME: PlayerActionableInfo::isActionAllowed
// Address: 0x007ebd70
// This function checks whether a specified action (param_4) is allowed for the player.
// It accesses player state via a pointer at this+0x58 (likely to Player class).
// The switch cases cover action IDs 0x13-0x1b (19-27).

#include <cstdint>

class Player; // forward declare

class PlayerActionableInfo {
public:
    // Offset +0x58: pointer to Player object (or something similar)
    Player* m_player; // +0x58

    bool isActionAllowed(int param_2, int param_3, int actionId, int param_5);
};

// External functions
bool IsPlayerInCombat(); // FUN_00481660 - checks if player is in combat
bool IsPlayerDriving(); // FUN_00481640 - checks if player is driving
bool IsPlayerBusy(int actionId); // FUN_00690150 - maybe checks if specific action is busy
bool IsPlayerOnFoot(); // FUN_007f47a0 - checks if player is on foot
bool CanSwitchWeapon(Player* player); // FUN_007eba50 - checks weapon switch availability
bool IsPlayerInCover(); // FUN_008a4380 - checks if player is in cover
bool IsPlayerInCutscene(); // FUN_00481620 - checks if player is in cutscene
bool IsPlayerInAction(); // FUN_004a8f00 - checks if player is already performing an action
bool IsPlayerBusy2(Player* player); // FUN_007eb750 - another busy check
bool BaseActionAllowed(int a, int b, int c, int d); // FUN_007ab790 - base class default handler

// Global data
extern int g_maxSomething; // DAT_01205224 - perhaps max health or stamina
extern uint8_t* g_globalFlags; // DAT_0112a838 - global flag array, offset 0xcd used

bool PlayerActionableInfo::isActionAllowed(int param_2, int param_3, int actionId, int param_5) {
    bool result = false;

    switch (actionId) {
    case 0x13: // Action: Attack/Shoot?
        if (IsPlayerInCombat()) {
            // If in combat, check if this specific action is busy
            if (IsPlayerBusy(0x14)) { // 0x14 = a specific action index
                result = true;
            }
            return result;
        }
        // Not in combat, check driving
        if (!IsPlayerDriving()) {
            if (IsPlayerOnFoot() && m_player) {
                // Check a flag at player+0x2400, if zero then allow
                if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(m_player) + 0x2400) == 0) {
                    return true;
                }
            }
        }
        break;

    case 0x14: // Action: Switch Weapon?
        if (!IsPlayerDriving()) {
            // Not driving, allow if CanSwitchWeapon returns true
            result = CanSwitchWeapon(m_player);
            return result;
        }
        // Driving, check flag at player+0x241c
        if (m_player) {
            if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(m_player) + 0x241c) == 0) {
                return true;
            }
        }
        result = false;
        break;

    case 0x15: // Action: Sprint/ run?
        // Check global max (maybe stamina or health)
        if (g_maxSomething <= *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x74)) {
            return false;
        }
        // Then check if specific action is busy
        if (IsPlayerBusy(0x14)) {
            return false;
        }
        if (IsPlayerDriving()) {
            return false;
        }
        return true;

    case 0x16: // Action: Enter cover?
        if (!IsPlayerInCombat()) {
            result = IsPlayerInCover(); // actually check if we can enter? maybe inverted
            return result;
        }
        // In combat, default result false
        break;

    case 0x17: // Action: Leave cover?
        result = IsPlayerInCover();
        return result;

    case 0x18: // Action: Reload?
        if (IsPlayerInCombat()) {
            if (!IsPlayerOnFoot()) {
                result = false;
            } else {
                result = true;
            }
        } else {
            result = false;
        }
        // Also allow if driving and flag at player+0x2438 is zero
        if (IsPlayerDriving() && m_player) {
            if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(m_player) + 0x2438) == 0) {
                return true;
            }
        }
        break;

    case 0x19: // Action: Aim/ lock on?
        if (IsPlayerDriving()) {
            result = false;
        } else if (IsPlayerInCombat()) {
            result = false;
        } else {
            result = true; // initially true, but further checks
        }
        // Check flag at player+0x2454 and whether player is already in an action
        if (result && m_player) {
            if (*reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(m_player) + 0x2454) == 0 &&
                IsPlayerInAction()) {
                return true;
            }
        }
        // Otherwise return the result computed above (likely false)
        break;

    case 0x1a: // Action: Pause menu?
        if (!IsPlayerInCutscene()) {
            return false;
        }
        // Check global flag at 0xcd
        if (*(g_globalFlags + 0xcd) == 0) {
            return false;
        }
        return true;

    case 0x1b: // Action: Open map?
        if (!IsPlayerInCover() && m_player) {
            if (!IsPlayerBusy2(m_player)) {
                return true;
            }
        }
        return false;

    default:
        // Fallback to base class handler
        result = BaseActionAllowed(param_2, param_3, actionId, param_5);
    }

    return result;
}