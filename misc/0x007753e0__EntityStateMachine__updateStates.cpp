// FUNC_NAME: EntityStateMachine::updateStates
// Function address: 0x007753e0
// Reconstructed from Ghidra decompilation. This appears to be a state machine update for
// an entity or component, handling transitions between states (IDs 8, 16, 32, 64).
// Offsets relative to 'this' (param_1):
//   +0x48: pointer to some base object (vtable at +0x00)
//   +0x5c: pointer to state data structure (stateID at +0x11c)
//   +100 : flags (bit 4 used for termination check)

void __fastcall EntityStateMachine::updateStates(EntityStateMachine* thisPtr)
{
    char cVar1;
    int iVar2;
    undefined4 uVar3;
    int* piVar4;
    undefined8 local_9c;
    undefined4 local_94;
    undefined8 local_90;
    undefined4 local_88;
    undefined4 local_84;
    undefined8 local_80;
    undefined4 local_78;
    undefined4 local_74;
    undefined8 local_70;
    undefined4 local_68;
    undefined4 local_64;
    undefined8 local_60;
    undefined4 local_58;
    undefined4 local_54;
    undefined8 local_50;
    undefined4 local_48;
    undefined4 local_44;
    undefined8 local_40;
    undefined4 local_38;
    undefined4 local_34;
    undefined8 local_30;
    undefined4 local_28;
    undefined4 local_24;
    undefined4 local_14;

    // Access state data pointer at offset +0x5c
    int* stateData = *(int**)(thisPtr + 0x5c);
    if (stateData != NULL && stateData != (int*)0x48) {
        // Compute base of state data (possibly adjusting for embedded offset)
        int* stateBase;
        if (stateData == (int*)0) {
            stateBase = (int*)0;
        } else {
            stateBase = stateData - 0x48; // Subtract 0x48 bytes (18 ints)
        }
        int stateID = *(int*)(stateBase + 0x11c / 4); // stateID at offset 0x11c

        switch (stateID) {
        case 8: // state ID 8
            preUpdate(); // FUN_00774ea0: called before state logic
            // Get base object pointer at +0x48
            if (*(int*)(thisPtr + 0x48) == 0) {
                piVar4 = (int*)0;
            } else {
                piVar4 = (int*)(*(int*)(thisPtr + 0x48) - 0x48);
            }
            iVar2 = *piVar4; // vtable pointer
            uVar3 = getInputParam(); // FUN_007254f0: retrieves some parameter
            (**(code**)(iVar2 + 0x1c))(uVar3); // vtable function at +0x1c (likely onEnterState)

            // Check termination flag (bit 4 of flags at +100)
            if ((*(unsigned int*)(thisPtr + 100) >> 4 & 1) != 0) {
                if (*(int*)(thisPtr + 0x48) != 0) {
                    terminateState(); // FUN_0072d8b0: cleanup/kill
                    return;
                }
                goto cleanup_and_return;
            }
            break;

        case 0x10: // state ID 16
            preUpdate();
            // Similar to case 8, but also calls another vtable function
            if (*(int*)(thisPtr + 0x48) == 0) {
                piVar4 = (int*)0;
            } else {
                piVar4 = (int*)(*(int*)(thisPtr + 0x48) - 0x48);
            }
            iVar2 = *piVar4;
            uVar3 = getInputParam();
            (**(code**)(iVar2 + 0x1c))(uVar3);

            // Second vtable call at +0x20
            if (*(int*)(thisPtr + 0x48) == 0) {
                piVar4 = (int*)0;
            } else {
                piVar4 = (int*)(*(int*)(thisPtr + 0x48) - 0x48);
            }
            iVar2 = *piVar4;
            uVar3 = getOtherInputParam(); // FUN_007255b0
            (**(code**)(iVar2 + 0x20))(uVar3); // vtable function at +0x20 (onUpdateState)

            if ((*(unsigned int*)(thisPtr + 100) >> 4 & 1) != 0) {
                if (*(int*)(thisPtr + 0x48) != 0) {
                    terminateState();
                    return;
                }
                goto cleanup_and_return;
            }
            break;

        case 0x20: // state ID 32
            // Prepare local structures from global constant (likely identity/zero)
            local_84 = 0;
            local_74 = 0;
            local_64 = 0;
            local_54 = _DAT_00d5780c; // Some global constant (maybe quaternion/vector)

            // Check transition condition via some validation function
            cVar1 = checkTransitionCondition(&local_90); // FUN_00725280
            if (cVar1 == '\0') {
                *(unsigned int*)(thisPtr + 100) |= 4; // Set bit 2 as error flag
                return;
            }

            preUpdate();
            // Initialize more locals from the prior local_90 etc.
            local_44 = 0;
            local_34 = 0;
            local_24 = 0;
            local_14 = _DAT_00d5780c;
            local_9c = local_60;
            local_40 = local_80;
            local_38 = local_78;
            local_94 = local_58;
            local_50 = local_90;
            local_48 = local_88;
            local_30 = local_70;
            local_28 = local_68;

            // Call vtable functions with the assembled parameters
            if (*(int*)(thisPtr + 0x48) == 0) {
                piVar4 = (int*)0;
            } else {
                piVar4 = (int*)(*(int*)(thisPtr + 0x48) - 0x48);
            }
            // vtable +0x1c with pointer to local_9c (structure copy)
            (**(code**)(*piVar4 + 0x1c))(&local_9c);

            if (*(int*)(thisPtr + 0x48) == 0) {
                piVar4 = (int*)0;
            } else {
                piVar4 = (int*)(*(int*)(thisPtr + 0x48) - 0x48);
            }
            // vtable +0x20 with pointer to local_54 (the global constant)
            (**(code**)(*piVar4 + 0x20))(&local_54);

            if ((*(unsigned int*)(thisPtr + 100) >> 4 & 1) != 0) {
                if (*(int*)(thisPtr + 0x48) != 0) {
                    terminateState();
                    return;
                }
                goto cleanup_and_return;
            }
            break;

        case 0x40: // state ID 64
            // Only call the second vtable function
            if (*(int*)(thisPtr + 0x48) == 0) {
                piVar4 = (int*)0;
            } else {
                piVar4 = (int*)(*(int*)(thisPtr + 0x48) - 0x48);
            }
            iVar2 = *piVar4;
            uVar3 = getOtherInputParam();
            (**(code**)(iVar2 + 0x20))(uVar3);
            break;
        }
    }
    return;

cleanup_and_return:
    terminateState();
    return;
}