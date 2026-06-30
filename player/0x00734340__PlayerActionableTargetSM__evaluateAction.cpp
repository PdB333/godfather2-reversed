// FUNC_NAME: PlayerActionableTargetSM::evaluateAction
// Function address: 0x00734340
// Evaluates the appropriate action (0=none, 1=melee, 2=fire weapon) based on player state and input.
// Returns: 0 (no action), 1 (melee attack), 2 (fire weapon)
int __thiscall PlayerActionableTargetSM::evaluateAction(PlayerObject* thisPtr, int param2) // param2 unused? possibly a context
{
    float ratio; // aspect ratio or speed ratio
    char flag; // temp for various checks
    int iVar3;
    int iVar4;
    int result;
    float fVar1;
    float10 floatA; // from virtual call at vtable+0xC0
    float10 floatB; // from virtual call at vtable+0xC4

    result = 0;

    // Get the player's current game state pointer (global + 4)
    if (*(int**)(DAT_012233a0 + 4) == 0) {
        iVar4 = 0;
    } else {
        iVar4 = **(int**)(DAT_012233a0 + 4) + -0x1f30; // offset to some subobject
    }

    // Check if player is not in a state that blocks this (byte at offset 0x6E3)
    if ((thisPtr->flagsBlockingAction == 0) && (iVar4 != 0)) {
        flag = FUN_00734150(); // check something global (timer? blocked?)
        if (flag == 0) {
            flag = FUN_007341f0(param2); // check param2 condition
            if (flag != 0) {
                flag = FUN_007a4900(thisPtr); // check if allowed to take action (e.g., weapon ready)
                if (flag != 0) {
                    iVar3 = FUN_00691810(); // check if game is paused or in UI mode
                    if ((iVar3 == 0) || ((*(uint*)(iVar4 + 0x8e0) >> 10 & 1) == 0)) {
                        // Get current "move" and "look" speeds from vtable
                        floatA = (float10)(thisPtr->vtable->getMoveSpeed)();  // vtable+0xC0
                        floatB = (float10)(thisPtr->vtable->getLookSpeed)();  // vtable+0xC4

                        // Get pointer to some component (weapon or animation) stored at offset 0x2004
                        if (thisPtr->componentPtr == 0) {
                            iVar4 = 0;
                        } else {
                            iVar4 = thisPtr->componentPtr + -0x48; // adjust base
                        }
                        fVar1 = *(float*)(iVar4 + 0x100); // some threshold (e.g., fire weapon speed)

                        if (thisPtr->componentPtr == 0) {
                            iVar4 = 0;
                        } else {
                            iVar4 = thisPtr->componentPtr + -0x48;
                        }
                        // Compare ratio of lookSpeed / moveSpeed to two thresholds
                        if ((float)(floatB / (float10)(float)floatA) < *(float*)(iVar4 + 0x104)) {
                            flag = FUN_0072c080(0x3c); // check if input button 60 (fire) is pressed
                            if (flag == 0) {
                                return 2; // action 2: fire weapon
                            }
                        }
                        if ((float)(floatB / (float10)(float)floatA) < fVar1) {
                            flag = FUN_0072c080(0x3b); // check if input button 59 (melee) is pressed
                            if (flag == 0) {
                                result = 1; // action 1: melee attack
                            }
                        }
                    }
                }
            }
        }
    }
    return result; // default 0: no action
}