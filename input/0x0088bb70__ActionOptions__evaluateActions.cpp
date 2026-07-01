// FUNC_NAME: ActionOptions::evaluateActions

void __thiscall ActionOptions::evaluateActions(ActionOptions* this)
{
    byte* pbVar1;
    bool bSkipForCurrentPlayer;
    char cCheckBlocked;
    int iCostSum;
    uint uPlayerIndex;
    uint uWeightedValue;
    int iCurrentActionPtr;
    int iOtherActionPtr;
    int iActionDelta;
    float fTimeFactor;
    float fNewTime;
    uint uLocal_20;                 // loop counter
    uint uLocal_18;                 // currentAction's weight/priority
    uint uLocal_14;                 // accumulated weight sum
    uint uNumActions;               // number of potential actions
    int iActionBase;                // base pointer for current action
    float fActionTime;              // action time from global DAT

    // Prepare and sort/setup action list
    FUN_0088b2b0(*(int*)(this + 0x8c), *(int*)(this + 0x90), uLocal_10);   // sortActionList?

    uLocal_14 = 0;
    // Determine base for "current action" context
    if (*(int*)(this + 0x278) == 0) {
        iCurrentActionPtr = 0;
    } else {
        iCurrentActionPtr = *(int*)(this + 0x278) + -0x48;
    }

    // Compute number of actions from the range [0x8c, 0x90)
    uNumActions = (*(int*)(this + 0x90) - *(int*)(this + 0x8c)) >> 2;
    uPlayerIndex = (uint)*(byte*)(this + 0xcc);   // player/controller index

    // Check if we should skip actions that are already in progress for this player
    bSkipForCurrentPlayer = false;
    if (((*(char*)(this + uPlayerIndex + 0xbc) != '\0') && 
         (*(int*)(this + 0xb0 + uPlayerIndex * 4) != 0)) &&
        (*(int*)(this + 0xc0 + uPlayerIndex * 4) != 0)) {
        bSkipForCurrentPlayer = true;
    }

    uLocal_18 = 0;
    if (bSkipForCurrentPlayer) {
        uLocal_18 = *(uint*)(this + 0xc0 + uPlayerIndex * 4);   // current action’s weight
    }

    uLocal_20 = 0;
    if (uNumActions != 0) {
        do {
            // Action pointer from the list
            iActionBase = *(int*)(*(int*)(this + 0x8c) + uLocal_20 * 4);
            // Check if this action’s base time exceeds the global max time
            if (*(float*)(iActionBase + 0xc) <= DAT_00e54254 && DAT_00e54254 != *(float*)(iActionBase + 0xc)) break;

            iActionDelta = FUN_00888080(iActionBase);   // get action cost/delta
            uWeightedValue = FUN_0088ee20();            // get current pressure time

            // If we have an active action for this player, adjust weight
            if (((*(int*)(this + 0xb0 + (uint)*(byte*)(this + 0xcc) * 4) != 0) &&
                 (iOtherActionPtr = *(int*)(this + 0xb0 + (uint)*(byte*)(this + 0xcc) * 4),
                 *(int*)(iOtherActionPtr + 0x6c) != 0)) &&
                (iOtherActionPtr = FUN_00446100(iOtherActionPtr + 0x70, 0), iOtherActionPtr != 0)) {
                if (*(int*)(this + 0x278) == 0) {
                    iCurrentActionPtr = 0;
                } else {
                    iCurrentActionPtr = *(int*)(this + 0x278) + -0x48;
                }
                if (iOtherActionPtr == iCurrentActionPtr) {
                    uWeightedValue -= *(int*)(*(int*)(this + 0xb0 + (uint)*(byte*)(this + 0xcc) * 4) + 0x6c);
                }
            }

            if (bSkipForCurrentPlayer) {
                cCheckBlocked = FUN_0088e5f0(*(int*)(iActionBase + 8));
                if (cCheckBlocked == '\0') {
                    if (uLocal_18 < uWeightedValue) {
                        uWeightedValue -= uLocal_18;
                    } else {
                        uWeightedValue = 0;
                    }
                    goto LAB_0088bd20;
                }
            } else {
LAB_0088bd20:
                uLocal_14 += iActionDelta;   // accumulate cost
                if (uWeightedValue < uLocal_14) break;

                // Determine time factor based on action flags
                if (*(int*)(this + 0x278) == 0) {
                    iCurrentActionPtr = 0;
                } else {
                    iCurrentActionPtr = *(int*)(this + 0x278) + -0x48;
                }
                uWeightedValue = *(uint*)(iCurrentActionPtr + 0x5c);
                fActionTime = DAT_00d62bd4;   // default time
                if (((uWeightedValue & 4) == 0) && (fActionTime = DAT_00e448cc, (uWeightedValue & 2) == 0) &&
                    (fActionTime = DAT_00d5e288, (uWeightedValue & 1) == 0)) {
                    if ((uWeightedValue & 8) == 0) {
                        fActionTime = *(float*)(iActionBase + 0xc);
                    } else {
                        fActionTime = 0.0;
                    }
                }

                // Check for special type 3 component (player?)
                float fExtraTime = 0.0;
                if (((*(int*)(iActionBase + 0x40) != 0) &&
                     (iOtherActionPtr = *(int*)(*(int*)(iActionBase + 0x40) + 4), iOtherActionPtr != 0)) &&
                    ((iOtherActionPtr = FUN_004025a0(iOtherActionPtr), iOtherActionPtr == 0 ||
                     (*(int*)(iOtherActionPtr + 0x24) != 3)))) {
                    fExtraTime = 0.0;
                } else {
                    fExtraTime = DAT_00e448cc;   // maybe idle time
                }

                fNewTime = *(float*)(iActionBase + 0xc) + fExtraTime + fActionTime;

                if ((*(short*)(iActionBase + 0x12) == 0) && (*(char*)(this + 0xad) != '\0')) {
                    // Action is not yet started and entity is active -> apply start time
                    FUN_0088ae10(iActionBase, (int)fNewTime);   // maybe setActionStartTime
                    int local_8 = iActionBase;
                    FUN_00888410(&local_8);                    // maybe add to active list
                    int iChild = *(int*)(iActionBase + 0x14);
                    // If current bounds are within target bounds and no blocking flag
                    if (((*(float*)(iChild + 0x30) <= *(float*)(iChild + 0x40) ||
                          *(float*)(iChild + 0x30) == *(float*)(iChild + 0x40)) &&
                         (*(float*)(iChild + 0x34) <= *(float*)(iChild + 0x44) ||
                          *(float*)(iChild + 0x34) == *(float*)(iChild + 0x44))) &&
                        ((*(float*)(iChild + 0x38) <= *(float*)(iChild + 0x48) ||
                          *(float*)(iChild + 0x38) == *(float*)(iChild + 0x48))) &&
                        ((*(byte*)(iChild + 0x54) & 8) == 0)) {
                        FUN_00429430(*(int*)(iActionBase + 8), iChild + 0x30, iChild + 0x40); // apply bounds
                    }
                } else {
                    // Action already started, just update time
                    int iComp = FUN_004025a0(*(int*)(iActionBase + 4));
                    float fCompTime;
                    if (iComp == 0) {
                        fCompTime = 0.0;
                    } else {
                        fCompTime = *(float*)(iComp + 0x48);
                    }
                    if ((int)fCompTime != (int)fNewTime) {
                        FUN_0088acb0(iActionBase, (int)fNewTime); // set action time
                    }
                }

                pbVar1 = (byte*)(*(int*)(iActionBase + 0x14) + 0x51);
                *pbVar1 = *pbVar1 | 0x10;   // mark action processed
            }
            uLocal_20++;
        } while (uLocal_20 < uNumActions);
    }

    FUN_0088bad0();   // finalize evaluation
    return;
}