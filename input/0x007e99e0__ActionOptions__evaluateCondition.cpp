// FUNC_NAME: ActionOptions::evaluateCondition
// Function at 0x007e99e0 - Evaluates various conditions for player actions based on condition ID (param4 - 0x13).
// Uses member fields:
//   this+0x30: m_conditionTimer (float)
//   this+0x58: m_playerData (pointer to PlayerData structure)
//   this+0x7c: m_stateMachine (pointer to state machine object with virtual functions)
// Condition IDs (0x13..0x17) map to cases 0..4.

bool __thiscall ActionOptions::evaluateCondition(int this, int param2, int param3, int conditionId, int param5)
{
    bool result = false;
    int currentState;          // iVar3
    int otherState;            // iVar4
    int actionAnimId;          // uVar5

    int switchIndex = conditionId - 0x13;
    switch (switchIndex) {
    case 0:
        // Get current state from the state machine (virtual call)
        currentState = (**(int (__thiscall ***)(int))(**(int **)(this + 0x7c) + 0x34))();
        // Check a flag in player data at offset 0x1b94 bit 4 (0x10) - possibly "CANNOT_ATTACK"
        if ((*(uint *)(*(int *)(this + 0x58) + 0x1b94) & 0x10) == 0) {
            // currentState is at offset 0x38 from the state machine's some internal data
            int stateCode = *(int *)(currentState + 0x38);
            if (stateCode == 1 || stateCode == 2) {
                actionAnimId = 0x23;   // e.g., ANIM_MELEE_ATTACK
            } else {
                if (stateCode != 3) {
                    return false;
                }
                actionAnimId = 0x24;   // e.g., ANIM_FIREARM_ATTACK
            }
            if (triggerAction(actionAnimId)) {
                return true;
            }
        }
        break;

    case 1:
        // Compare current state's target with a global value (e.g., desired state)
        currentState = (**(int (__thiscall ***)(int))(**(int **)(this + 0x7c) + 0x34))();
        otherState = getGlobalStateID();   // likely returns target state from somewhere
        if (*(int *)(currentState + 0x30) == otherState) {
            return true;
        }
        return false;

    case 2:
        // Delegates to another condition check using player data pointer
        result = isSpecialConditionMet(*(int *)(this + 0x58));
        break;

    case 3:
        // Simple timer check - condition timer must exceed global threshold
        if (*(float *)(this + 0x30) > *DAT_00d6fdd0) {
            return true;
        }
        return false;

    case 4:
        // Combined check: global flag and timer
        if (isGlobalFlagSet() && *DAT_00d6fdd4 < *(float *)(this + 0x30)) {
            return true;
        }
        return false;

    default:
        // Fallback to base class evaluator (maybe ActionOptions::evaluateDefault)
        result = baseEvaluateCondition(param2, param3, conditionId, param5);
    }

    return result;
}