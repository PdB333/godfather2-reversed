// FUNC_NAME: PlayerEligibilityChecker::isEligibleForAction
// Address: 0x008c8110
// Role: Checks whether a given action (type) is allowed based on player state and game mode.
// Fields: this+0x04 = actionType (uint32), this+0x08 = pPlayerContext (PlayerContext*)
// PlayerContext offsets: +0x5c = flags (uint32), +0x5f = flags2 (byte)

#include <cstdint>

class PlayerEligibilityChecker {
public:
    bool __thiscall isEligibleForAction() {
        // +0x04: actionType - e.g., 1 = kAction_Recruit
        if (*(uint32_t*)(this + 4) == 1) {
            // sub_791230: likely checks if game is in freeroam/player controllable mode
            char isFreeroam = sub_791230(); // FUN_00791230
            if (isFreeroam != 0) {
                uint8_t* pContext = *(uint8_t**)(this + 8);
                // +0x5f: flags2 - bit0 cleared means not in combat/dialog?
                if ((*(pContext + 0x5f) & 1) == 0) {
                    // sub_791750: likely returns current crew count or state value
                    int crewCount = sub_791750(); // FUN_00791750
                    // +0x5c: flags - bit5 cleared means not in vehicle?
                    if (crewCount < 6 && (*(uint32_t*)(pContext + 0x5c) & (1 << 5)) == 0) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};
```