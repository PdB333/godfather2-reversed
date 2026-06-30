// FUNC_NAME: AICharacter::updateMovement
void __thiscall AICharacter::updateMovement(int this) // 0x006a6760
{
    // +0x6a0: pointer to some count limit (max path nodes? target list size?)
    int* maxIndex = (int*)(this + 0x6a0);
    // +0x69c: current index
    if (*(int*)(this + 0x69c) <= *maxIndex) {
        return;
    }

    // Get a target entity handle (likely nearest enemy or point of interest)
    int targetHandle;
    if (!FUN_005e7ba0(&targetHandle, 0)) { // Query function, param 0 = ? 
        return;
    }

    // Get distance to target (out parameter)
    float distance;
    if (!FUN_005e7a40(targetHandle, &distance)) {
        return;
    }

    // +0x694: some state field (0 or 0x48 = 72 = "idle"?)
    int state = *(int*)(this + 0x694);
    if (state == 0 || state == 0x48) {
        // +0x520: action state (0 = not in an action?)
        if (*(int*)(this + 0x520) == 0) {
            // +0x6b8: flag (like "attacking"?)
            // +0x6a4: another flag
            if (*(int*)(this + 0x6b8) == 0 && *(int*)(this + 0x6a4) != 0) {
                FUN_006a65d0(); // Start some behavior
                if (*(int*)(this + 0x520) != 0) {
                    // Re-evaluate
                    this->updateMovement();
                    return;
                }
            }

            FUN_006a5d20(); // Idle/patrol update?

            // +0x68c: next state candidate
            int nextState = *(int*)(this + 0x68c);
            if (nextState != 0 && nextState != 0x48) {
                // +0x524: current state
                int currentState = *(int*)(this + 0x524);
                if (currentState != nextState) {
                    if (currentState != 0 && currentState != 0x48) {
                        FUN_006a40b0(0); // Exit current state
                    }
                    // Transition to nextState
                    FUN_006a5380((int*)(this + 0x68c));
                    // Re-enter state? (if starting, FUN_006a40b0 with 1)
                    if (*(int*)(this + 0x524) == 0) {
                        FUN_006a40b0(1);
                    } else {
                        FUN_006a40b0(1);
                    }
                }
            }
            goto LAB_006a6909;
        }

        // Already in an action (non-zero +0x520)
        if (*(int*)(this + 0x6b8) == 0 && *(int*)(this + 0x6a4) != 0) {
            FUN_006a65d0(); // Continue action
        }
        FUN_006a5d20();

        // +0x14, +0x18, +0x1c: position vector (x,y,z)
        float dx = distance - *(float*)(this + 0x14);
        // Note: the decompiled uses local_30, fStack_2c, local_28 for the new position? 
        // Actually after FUN_005e7a40, local_30 is distance, but later they use local_28 and fStack_2c
        // That's confusing. Let's re-analyze:
        // The code after FUN_006a5d20 does:
        // fVar5 = local_28 - *(float*)(this+0x1c); (z?)
        // fVar4 = fStack_2c - *(float*)(this+0x18); (y?)
        // fVar3 = local_30 - *(float*)(this+0x14); (x?)
        // But local_30 was distance? Actually FUN_005e7a40 might set multiple floats via stack.
        // It's likely that FUN_005e7a40 fills a Vector3 (local_30, fStack_2c, local_28) and also returns float distance? 
        // The prototype: might be FUN_005e7a40(handle, &vec3, &distance?) 
        // Since local_30 is reused, maybe the function writes to local_30 as x, fStack_2c as y, local_28 as z, and also returns distance in eax? 
        // But the call is FUN_005e7a40(local_3c, &local_30); so only one out param. 
        // Then local_28 and fStack_2c are uninitialized? No, they are local variables on stack.
        // Wait, the decompiled shows:
        // undefined4 local_3c;
        // undefined4 local_38;
        // int *local_34;
        // float local_30;
        // float fStack_2c;
        // float local_28;
        // So local_30, fStack_2c, local_28 are three floats. They are all local but not necessarily set by that call. 
        // Actually after the call to FUN_005e7a40, only local_30 is set. Then later they read local_28 and fStack_2c.
        // That would be UB. So the decompilation might be inaccurate. The original source likely assigned all three components.
        // Given the pattern, FUN_005e7a40 probably fills a Vector3 starting at &local_30. So local_30 is x, fStack_2c is y, local_28 is z.
        // Similarly, the position in the object is at +0x14 (x), +0x18 (y), +0x1c (z).
        // So the difference squared calculation uses:
        // dz = local_28 - (this+0x1c)
        // dy = fStack_2c - (this+0x18)
        // dx = local_30 - (this+0x14)
        // If squared distance <= a global threshold, skip updating position.
        float dz = local_28 - *(float*)(this + 0x1c);
        float dy = fStack_2c - *(float*)(this + 0x18);
        float dx = local_30 - *(float*)(this + 0x14);
        float distSq = dx*dx + dy*dy + dz*dz;
        if (distSq > _DAT_00d5d798) {
            // Update position
            *(ulonglong*)(this + 0x14) = CONCAT44(fStack_2c, local_30); // pack x,y into 64-bit (likely two floats)
            *(float*)(this + 0x1c) = local_28; // z
        }
    }

    FUN_006a57c0(); // Common update (movement application?)

LAB_006a6909:
    // +0x524: current state again
    int currentState = *(int*)(this + 0x524);
    if (currentState != 0 && currentState != 0x48) {
        char buffer[32];
        FUN_00826540(buffer); // Format a string (likely debug)
        // +0x10: some parameter (ID?)
        uint param = *(uint*)(this + 0x10);
        // Global: DAT_0112a53c + 0x70 -> pointer to something (maybe a debug overlay manager)
        int overlayPtr = *(int*)(DAT_0112a53c + 0x70);
        FUN_006a44b0(maxIndex, buffer, overlayPtr, &local_30, param); // Update debug visualization
    }
}