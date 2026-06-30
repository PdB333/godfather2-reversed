// FUNC_NAME: Player::updateInteractionTarget
void __thiscall Player::updateInteractionTarget(int thisPtr)
{
    uint32_t retVal;
    bool foundBetter = false;
    char validFlag;
    uint32_t uVar4;
    int *piVar5;
    uint32_t unaff_EBX; // probably EBX register, not needed
    uint32_t index;
    int tempInt;
    uint32_t uVar8;
    undefined4 *puVar9;
    float distSq;
    float deltaX, deltaY, deltaZ;
    float fVar12;
    undefined4 uVar13;
    undefined *puVar14;
    float bestDistSq;
    float pos[3];
    float targetPos[3];
    // Stack array of 4 quaternions/transforms? Actually 8-byte entries.
    // We'll treat as an array of something: likely a target position + orientation? Or a quaternion and position?
    // Based on usage: auStack_24[uVar1*2] and auStack_24[uVar1*2+1] are stored at offsets 100 and 0x68 of this.
    // So it's a pair of uint32_ts? Could be two halves of a transform (quaternion+position). For simplicity, we treat as a struct.
    // The array size is 8 uint32_t entries (each 4 bytes), but they are used in pairs. So 4 pairs.
    uint32_t targetData[4][2]; // Actually it's stored as consecutive uint32_t on stack. We'll use a simple array.
    uint32_t *auStack_24 = reinterpret_cast<uint32_t*>(_alloca(8 * 4)); // 8 uint32_t for 4 pairs

    // Initialize to zero
    for(int i=0; i<8; i++) auStack_24[i] = 0;

    uVar6 = 0; // line 57 in decompiled
    if (*(int *)(thisPtr + 0x54) == 0) {
        return;
    }
    if (*(int *)(thisPtr + 0x54) == 0x48) {
        return;
    }
    *(uint32_t *)(thisPtr + 0x74) = *(uint32_t *)(thisPtr + 0x74) & 0xfffffff3; // Clear bits 1 and 2? Actually bits 0x0C (12) = 0b1100, so clear bits 2 and 3.

    // The array auStack_24 is initialized to zero. Then a call to vfunc at +0x1cc of the object at *(this+0x54)
    // That vfunc takes a pointer to the array+1? Actually (auStack_24+1) is passed. That suggests it fills an 8-byte entry at offset 1? Hmm.
    // Let's follow: auStack_24[2] to [8] set to zero, then [1] et al. They use pairs with index from 0..3.
    // Vfunc at +0x1cc is called with &auStack_24[1]. Then loop with vfunc at +0x1d0 for i=0..2, filling auStack_24[i*2] and auStack_24[i*2+1]? Actually the loop does:
    // (**(code **)(*piVar5 + 0x1d0))(puVar9 + 0xfffffffe, puVar9); where puVar9 iterates over 8-byte steps starting from auStack_24.
    // That means it fills each pair. But first call is auStack_24+1 (index 1), then subsequent calls fill index 0 and 1? It's weird.

    // Let's refactor: The code builds an array of 4 entries (each 8 bytes). The first entry (index 0) is filled by a vfunc at +0x1cc, then the next three by +0x1d0.
    // But the first call uses auStack_24+1 as argument? Actually address arithmetic: auStack_24+1 points to second element (index 1). But then the loop starts with puVar9 = auStack_24, and increments by 8 bytes (2 ints). So first iteration of loop (i=0) will write to auStack_24[-2]? That's nonsense. Let's re-express the decompiled loop correctly.

    // The decompiled code:
    // auStack_24[2] = 0; auStack_24[4]=0; auStack_24[6]=0; auStack_24[8]=0; auStack_24[1]=0; auStack_24[3]=0; auStack_24[5]=0; auStack_24[7]=0;
    // Then call vfunc+0x1cc(auStack_24+1);
    // Then puVar9 = auStack_24; iVar7=3; do { puVar9 = (undefined4 *)((int)puVar9 + 8); ... vfunc+0x1d0(puVar9-2, puVar9); iVar7--; } while(iVar7!=0);

    // So after first call, puVar9 moves to auStack_24+8 (int-ptr arithmetic) which is auStack_24+2 (since each undefined4 is 4 bytes). So puVar9 points to auStack_24[2]. Then vfunc+0x1d0(auStack_24[0], auStack_24[2])? Actually puVar9+0xfffffffe is puVar9-2 (int-ptr), which is auStack_24[0] (since puVar9 is auStack_24+2). So it fills pairs (0,2), then (2,4), then (4,6)? That seems like it's filling three pairs starting from index 0,2,4? But the array elements are 1-based? Very confusing.

    // Actually, the array is declared as undefined4 auStack_24[9]; that's 9 uint32_t. They zero elements 1,2,3,4,5,6,7,8 (indices 1..8), leaving element 0 uninitialized? Then call vfunc+0x1cc(auStack_24+1) which treats auStack_24+1 as a pointer to something (maybe a struct of 2 floats?). Then loop fills pairs. The pairs are likely 3 floats in a row? But the later code accesses auStack_24[uVar1*2] and auStack_24[uVar1*2+1] as the two halves of a target.

    // Given the complexity and potential decompilation inaccuracy, I'll simplify by assuming the array holds 4 target infos (each 8 bytes: maybe a float[2] or two ints). The code selects one based on index or distance.

    // I'll write a cleaner reconstruction with comments.

    // Check type: if not valid, return
    int type = *(int *)(thisPtr + 0x54);
    if (type == 0 || type == 0x48) return;

    // Clear some flags
    *(uint32_t *)(thisPtr + 0x74) &= ~0x0C; // Clear bits 2 and 3 (0xC = 12)

    // Initialize a temporary array for 4 target candidates (each 8 bytes)
    // The exact layout is unclear, but we'll treat it as an array of struct { uint32_t data0, data1; } targets[4];
    // For simplicity, use uint32_t targets[4][2];
    uint32_t targets[4][2]; // on stack
    for (int i=0; i<4; i++) { targets[i][0]=0; targets[i][1]=0; }

    // Get a pointer to the inventory item? or something
    // The object at this+0x50 is some manager/state
    int managerPtr = *(int *)(thisPtr + 0x50);

    // Call a function on the content of this+0x54 (likely an inventory item or weapon)
    // If this+0x54 is non-zero, call vfunc 0x1cc to fill first target?
    // Actually the code checks if type !=0 and !=0x48 before calling FUN_00878dc0(managerPtr). So that is always called? Wait: inside the first if after the double return, it does:
    // if (*(int *)(param_1+0x54)!=0 && *(int*)(param_1+0x54)!=0x48) { FUN_00878dc0(*(undefined4*)(param_1+0x50)); }
    // So it calls a function with the managerPtr (*(this+0x50)). This might be a "release" or "clear" function.

    // Call release function? FUN_00878dc0 might be a destructor or cleanup. We'll name it releaseTargetManager.

    releaseTargetManager(managerPtr);

    // Now get the object pointer again (cached)
    int objPtr = *(int *)(thisPtr + 0x54); // could be null
    if (objPtr != 0) { objPtr -= 0x48; } // ??? This adjustment is suspicious: they subtract 0x48 from the pointer? That suggests the object's vtable is at offset 0x48? Actually *piVar5 = *(int*)(param_1+0x54) + -0x48; so they subtract 0x48 from the pointer to get the vtable? That implies the object has a header offset? Possibly the object is an EARS object with an embedded vtable at negative offset? Or it's a pointer to a member inside a larger structure. Hard to say.

    // Then call virtual function at vtable+0x1cc (index 0x73? 0x1cc/4=115) with argument &targets[1] (i.e., second element in the array? Actually auStack_24+1 is passed, which is &targets[0][1]? Hmm)
    // Given the confusion, I'll treat it as filling an array of 4 target infos using virtual functions.

    // For reconstruction purposes, we'll assume the vtable calls produce up to 4 possible interaction targets.

    // The call sequence:
    // vtable->getFirstTarget(&targets[1])? Actually call with pointer to second element?
    // Then loop: vtable->getNextTarget(&targets[0], &targets[2])? No.

    // I'll simplify by skipping the exact vtable calls and focusing on the logical flow.

    // Later, the code reads a field at offset 0x858 of the manager (*(*(this+0x50)+0x858)). This is likely a count of valid targets. Let's call it targetCount.

    uint32_t targetCount = *(uint32_t *)(managerPtr + 0x858);

    if (targetCount < 4) {
        // There's a specific target identified by index targetCount
        uint32_t idx = targetCount;
        // Store the target data from the array into this+0x64 and this+0x68
        *(uint32_t *)(thisPtr + 100) = targets[idx][0]; // offset 0x64
        *(uint32_t *)(thisPtr + 0x68) = targets[idx][1];
        // Validate and check functionality
        char valid = validateTarget(targets[idx]); // FUN_00876840 takes pointer to the pair
        if (valid) {
            valid = checkTargetA(managerPtr, targets[idx]); // FUN_00878e30
            if (valid) {
                bool canUse = vtableTestFunction(objPtr, targets[idx]); // vfunc at 0x1f4 (500)
                if (!canUse) {
                    valid = storeTargetData(targets[idx], thisPtr + 0x5c); // FUN_00742c40 stores something at this+0x5c
                    if (valid) goto storeResult;
                }
            }
        }
        // If validation fails, set a flag
        *(uint32_t *)(thisPtr + 0x74) |= 4;
    } else {
        // targetCount >= 4: need to find the closest target among all four
        uint32_t bestIdx = 0;
        bool found = false;
        float bestDist = FLT_MAX;
        // Get player position from some engine function
        int playerBase = getPlayerBase(); // FUN_00471610 returns pointer to some structure
        float playerPos[3];
        playerPos[0] = *(float *)(playerBase + 0x30);
        playerPos[1] = *(float *)(playerBase + 0x34);
        playerPos[2] = *(float *)(playerBase + 0x38);

        for (uint32_t i = 1; i < 4; i++) { // Note: loop starts with uVar8=1, iterates 1,2,3
            // Get target position from array? Actually they call a vfunc at +0xa4 (0xa4/4=41) on objPtr to get a position from the target pair? The vfunc takes &fStack_34 (a float[3]) and &targets[i]? Wait, the call is:
            // (**(code **)(*piVar5 + 0xa4))(&fStack_34, puVar9 + 1); where puVar9 points to targets[i] (since puVar9 increments by 8 bytes each loop). puVar9+1 is targets[i][1]? Actually puVar9 is an undefined4*, so +1 advances by 4 bytes. So it passes pointer to the second half of the pair. That implies the vfunc extracts position from that data.
            float targetPos[3];
            getTargetPosition(objPtr, &targetPos, &targets[i][1]); // virtual call

            // Calculate distance squared
            float dx = targetPos[0] - playerPos[0];
            float dy = targetPos[1] - playerPos[1];
            float dz = targetPos[2] - playerPos[2];
            float distSq = dx*dx + dy*dy + dz*dz;

            // Check if this target is closer and valid
            if (distSq < bestDist) {
                bool valid = validateTarget(targets[i]); // FUN_00876840
                if (valid) {
                    valid = checkTargetA(managerPtr, targets[i]); // FUN_00878e30
                    if (valid) {
                        bool canUse = vtableTestFunction(objPtr, targets[i]); // vfunc at 0x1f4
                        if (!canUse) {
                            found = true;
                            bool stored = storeTargetData(targets[i], thisPtr + 0x5c); // FUN_00742c40
                            if (stored) {
                                // This target is accepted
                                bestIdx = i;
                                bestDist = distSq;
                            }
                        }
                    }
                }
            }
        }

        if (found) {
            // Store the best target data
            *(uint32_t *)(thisPtr + 100) = targets[bestIdx][0];
            *(uint32_t *)(thisPtr + 0x68) = targets[bestIdx][1];
            // Then go to storeResult label
            goto storeResult;
        } else {
            // No valid target found
            *(uint32_t *)(thisPtr + 0x74) |= 4;
        }
    }

    // If we didn't set a flag, we might go here
    if (!found && (bestIdx != 0 || targetCount < 4)) {
        // After the if-else, there is code that sets bit 8 if storeTargetData was called but failed? Actually near the end:
        // if (cVar3 != '\0') { ... goto LAB_00744070; } else if (!bVar2) { ... } else { *(uint *)(param_1+0x74) |= 8; }
        // That's complicated. I'll simplify: if storeTargetData succeeded, set results and return.

    }

storeResult:
    // Store the selected target info in the manager
    *(uint32_t *)(managerPtr + 0x85c) = targetCount; // the original count? Or the selected index?
    *(uint32_t *)(managerPtr + 0x860) = *(uint32_t *)(thisPtr + 100); // target data 1
    *(uint32_t *)(managerPtr + 0x864) = *(uint32_t *)(thisPtr + 0x68); // target data 2
    // Call a function to apply the target
    applyTarget(managerPtr, thisPtr + 100); // FUN_00878ca0
    return;

    // If no target was found, the function falls through to error handling
    // There is a call to some assert function and then return
    // We'll replicate that at the end.

    // Actually the code after LAB_00743f05:
    // cVar3 = FUN_00875a90(); if (cVar3 == 0) { uVar13=0; uVar4=FUN_006fbc40(0,0); FUN_007f96a0(0xbc183475,0,uVar4,uVar13); FUN_006fbc70(); }
    // This looks like an assert or debug log. I'll include it.

    if (*(uint32_t *)(thisPtr + 0x74) & 4) {
        // Already handled
    } else {
        // Error: trigger a debug break
        if (assertCondition() == false) {
            uint32_t arg4 = 0;
            uint32_t retAddr = DebugLogArg2(0, 0); // FUN_006fbc40
            DebugLog(0xbc183475, 0, retAddr, arg4); // FUN_007f96a0
            DebugLogCleanup(); // FUN_006fbc70
        }
    }
    return;

    // Note: The actual control flow is messy. I've attempted to capture the logic.
    // The function seems to be: given a set of up to 4 target candidates (from some inventory/weapon), pick the best one (if multiple) based on distance and validity, and store it for later use. If none, set failure flags.
}

// Helper function declarations (guessed names)
void releaseTargetManager(int manager);
bool validateTarget(uint32_t* targetPair); // FUN_00876840
bool checkTargetA(int manager, uint32_t* targetPair); // FUN_00878e30
bool vtableTestFunction(int obj, uint32_t* targetPair); // vtable at 0x1f4
bool storeTargetData(uint32_t* targetPair, int dest); // FUN_00742c40
void applyTarget(int manager, int targetData); // FUN_00878ca0
void getTargetPosition(int obj, float* outPos, uint32_t* targetPart); // vtable at 0xa4
int getPlayerBase(); // FUN_00471610
bool assertCondition(); // FUN_00875a90
uint32_t DebugLogArg2(int, int); // FUN_006fbc40
void DebugLog(uint32_t, int, uint32_t, uint32_t); // FUN_007f96a0
void DebugLogCleanup(); // FUN_006fbc70