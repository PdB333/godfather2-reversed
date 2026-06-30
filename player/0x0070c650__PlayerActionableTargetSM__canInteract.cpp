// FUNC_NAME: PlayerActionableTargetSM::canInteract
// Address: 0x0070c650
// Role: Determines if this player can interact with a targeted object/entity based on state, distance, and targeting flags.

__thiscall uint8 PlayerActionableTargetSM::canInteract(void) {
    int* piVar1; // interactionTarget pointer at +0x374
    char cVar2;  // current state at +0x1ad
    int iVar3;   // temporary
    int iVar5;   // something from FUN_00471610
    int iVar6;   // base of interactionTarget - 0x48
    float fVar7, fVar8; // dx, dy
    uint8 result = 1;

    cVar2 = *(char*)(this + 0x1ad);
    // State must be either 0x1a (26) or 0x1b (27) to allow interaction
    if (cVar2 != 0x1a && cVar2 != 0x1b) {
        return 1;
    }

    piVar1 = (int*)(this + 0x374);
    if (*piVar1 == 0 || *piVar1 == 0x48) {
        // No valid interaction target, or target is a special marker (0x48 = 72, maybe "no target" sentinel)
        if (cVar2 != 0x1a && cVar2 != 0x1b) {
            return 1;
        }
        if (*(int*)(this + 0x2d4) == 0) {
            return 1;
        }
        if (*(int*)(this + 0x2d4) == 0x48) {
            return 1;
        }
        // Check if any of four interaction-related slots are in use
        if (*(int*)(this + 0x364) == 0 && *(int*)(this + 0x368) == 0 &&
            *(int*)(this + 0x36c) == 0 && *(int*)(this + 0x370) == 0) {
            return 1;
        }
        // Search for an actionable target from the list at +0x364
        iVar3 = FUN_00446100(this + 0x364, 0); // likely getFirstTarget(list)
        if (iVar3 != 0) {
            // Create/handle a specific object identified by hash 0x346d561a (maybe "Interact")
            uVar4 = FUN_0070afb0(iVar3, 0x346d561a);
            FUN_0070af00(uVar4);
        }
        // If we have a valid interactionTarget (not 0, not 0x48) and state is 0x1a, check a flag at +0x1a8
        if ((*piVar1 != 0 && *piVar1 != 0x48) && cVar2 == 0x1a) {
            iVar3 = *piVar1 == 0 ? 0 : *piVar1 - 0x48; // base of interactionTarget (subtract header offset)
            if (*(int*)(iVar3 + 0x1a8) == 0) goto LAB_0070c790; // flag false -> skip to distance check
        }
        if (cVar2 == 0x1b) {
            iVar3 = *piVar1 == 0 ? 0 : *piVar1 - 0x48;
            if (*(int*)(iVar3 + 0x1a8) == 1) goto LAB_0070c790;
        }
        // If target exists but flag doesn't match, release it and return
        if (*piVar1 != 0) {
            FUN_004daf90(piVar1); // release reference
            *piVar1 = 0;
            return 1;
        }
    } else {
        // *piVar1 is neither 0 nor 0x48 – we have a real target pointer
        // The following inner if is logically dead (always false) but present in original code
        if ((*piVar1 == 0 || *piVar1 == 0x48) && *piVar1 != 0) {
            // never executed
        }
LAB_0070c790:
        if (*piVar1 != 0 && *piVar1 != 0x48) {
            // Get player and target positions via two calls to FUN_00471610
            iVar3 = FUN_00471610(); // player transform?
            iVar5 = FUN_00471610(); // target transform?
            // Compute horizontal distance delta
            fVar8 = *(float*)(iVar5 + 0x38) - *(float*)(iVar3 + 0x38); // dz?
            fVar7 = *(float*)(iVar5 + 0x30) - *(float*)(iVar3 + 0x30); // dx?
            iVar6 = *piVar1 == 0 ? 0 : *piVar1 - 0x48; // base of target
            // Check if within interaction range
            if (sqrt(fVar8*fVar8 + fVar7*fVar7) <= *(float*)(iVar6 + 0x1b0) + interactionRadiusAdd) {
                // Also check vertical difference (masked for sign)
                float dZ = (float)((uint)(*(float*)(iVar5 + 0x34) - *(float*)(iVar3 + 0x34)) & interactionHeightMask);
                if (dZ <= interactionHeightLimit) {
                    // Set interaction flag (bit 0x10 at +0x39e)
                    *(uint16*)(this + 0x39e) |= 0x10;
                    return 1;
                }
            }
            result = 0;
        }
    }
    return result;
}