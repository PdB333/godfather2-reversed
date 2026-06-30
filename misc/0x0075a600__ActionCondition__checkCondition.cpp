// FUNC_NAME: ActionCondition::checkCondition
// Reconstructed from 0x0075a600 (EA EARS engine, The Godfather 2 x86)
// This is a virtual member function (__thiscall) that evaluates various conditions
// based on 'conditionType' parameter (param_4). The function returns true/false.
// The structure at 'this' has fields:
// +0x50 : unknown (used in case 12)
// +0x5c : likely a position/vector (used with FUN_0075a220)
// +0x68 : another parameter for FUN_0075a220 (e.g., target)
// +0x74 : pointer (checked for null in case 15)
// +0x7c : pointer to a sub-structure (e.g., animation state) at +0x24
// +0x94 : boolean flag (returned directly in case 18)
// +0x98 : float (compared against global thresholds in cases 16,17)
// +0x9c : 8 bytes (e.g., double) set from a global timer in case 12
// +0xa4 : 4 bytes (float?) set from timer in case 12
// +0xa8 : uint32 (counter, reset to 0 in cases 11 and 12)

// External functions (with guessed names):
// checkLineOfSight (0x0075a220) - checks visibility or path
// getTimerValue (0x00471610) - returns some time/position data (8+4 bytes at +0x30)
// AIStateCheck (0x006dc8e0) - hashed check on animation state
// isGlobalFlagSet (0x0054f460) - checks global boolean (DAT_00d5ef88)
// updateConditionPath (0x0075d3c0) - initializes path/position data
// baseClassCheckCondition (0x004ac640) - default handler for unknown condition types

// Global variables:
extern float g_conditionThreshold1;  // DAT_00d5c458
extern float g_conditionThreshold2;  // DAT_00d5eee4
extern bool g_globalFlag;            // DAT_00d5ef88
extern uint32_t g_unknownParam;      // DAT_00e44658

bool ActionCondition::checkCondition(
    int unused1,               // param_2 – likely ignored here
    int unused2,               // param_3
    int conditionType,         // param_4 – condition ID (mapped to switch)
    int unused3)               // param_5 – passed to base class default
{
    switch (conditionType - 10) {
    case 0:  // condition type 10
    case 3:  // condition type 13
        return true;

    case 1:  // condition type 11
        if (*(uint32_t*)(this + 0xa8) > 2) {
            int subObj = *(int*)(this + 0x7c);
            if (subObj != 0) {
                int animState = *(int*)(subObj + 0x24);
                if (animState != 0 && animState != 0x48) {
                    int adjustedState = (animState == 0) ? 0 : (animState - 0x48);
                    if (AIStateCheck(adjustedState, 0x383225a1) != 0) {
                        *(uint32_t*)(this + 0xa8) = 0;
                        return false;
                    }
                }
            }
            if (checkLineOfSight(this + 0x5c, *(uint32_t*)(this + 0x68)) == 0) {
                return !isGlobalFlagSet(g_globalFlag);
            }
        }
        break;

    case 2:  // condition type 12
        if (updateConditionPath(*(uint32_t*)(this + 0x50), this + 0x5c,
                                *(uint32_t*)(this + 0x68), g_unknownParam, 0) == 0) {
            return false;
        }
        {
            int timerAddr = getTimerValue();
            // Copy 12 bytes from timer structure: 8 at +0x30, 4 at +0x38
            *(uint64_t*)(this + 0x9c) = *(uint64_t*)(timerAddr + 0x30);
            *(uint32_t*)(this + 0xa4) = *(uint32_t*)(timerAddr + 0x38);
            if (checkLineOfSight((uint64_t*)(this + 0x9c), *(uint32_t*)(this + 0x68)) == 0) {
                *(uint32_t*)(this + 0xa8) = 0;
                return false;
            }
        }
        return false;

    case 4:  // condition type 14
        return checkLineOfSight(this + 0x5c, *(uint32_t*)(this + 0x68)) != 0;

    case 5:  // condition type 15
        return *(int*)(this + 0x74) == 0;

    case 6:  // condition type 16
        if (*(float*)(this + 0x98) <= g_conditionThreshold1) {
            return true;
        }
        break;

    case 7:  // condition type 17
        if (*(float*)(this + 0x98) <= g_conditionThreshold2) {
            return true;
        }
        return false;

    case 8:  // condition type 18
        return *(bool*)(this + 0x94);

    default:
        // Fallback to base class implementation
        return baseClassCheckCondition(unused1, unused2, conditionType, unused3);
    }
    return false;
}