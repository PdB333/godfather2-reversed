// FUNC_NAME: HUDTargetManager::updateTargetSelection

void __thiscall HUDTargetManager::updateTargetSelection(
    uint4 *this,
    uint4 unkParam,
    float4 *crosshairPos,
    float4 crosshairScreenPos,
    uint4 colorParam,
    uint targetMask,
    uint visibilityMask,
    TargetInfo *outTargetArray,
    int outTargetCount)
{
    bool isFirstPass;
    int i, bestIndex, prevTargetIndex, stickyCount;
    float bestScore, score, threshold;
    uint4 currentType, candidatePointer;
    uint4 *slotPtr;

    // Save context for later restoration
    int contextA = FUN_00422930();
    int contextB = FUN_00422940();
    if (contextB != 0) {
        FUN_00423610();
    }
    FUN_00422900();

    // Store crosshair position
    float4 storedCrosshair;
    storedCrosshair.x = crosshairPos->x;
    storedCrosshair.y = crosshairPos->y;
    storedCrosshair.z = crosshairPos->z;
    storedCrosshair.w = crosshairPos->w;

    // Begin rendering target indicator
    uint4 textureHandle = FUN_0060d860(0);
    FUN_006094d0(textureHandle);

    // Set target icon texture and size from class members
    uint4 targetIconTexture = this[0x805];   // +0x2014: target icon texture handle
    uint4 targetIconSize   = this[0x807];   // +0x201C: target icon size

    FUN_0060db20(0, targetIconSize, 0, 0);
    FUN_0060db20(4, targetIconTexture, 0, 0);
    FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000); // Set color scale? (1.0, 1.0)

    FUN_00609730(
        this[0x809], this[0x80a], this[0x80b], this[0x80c],
        0x3f800000, 0
    ); // +0x2024, 0x2028, 0x202C, 0x2030: maybe position/color
    FUN_00609810(0x31); // Set some render state

    FUN_00609730(0, 0, 0, 0, 0x3f800000, 0);

    bool isLockedOn = false; // local_38
    FUN_00613440(7);
    FUN_00613b70();
    FUN_00613e10(crosshairScreenPos); // Position crosshair on screen
    FUN_006143f0(this[0x811], this[0x812], this[0x814], this[0x813]); // Additional rendering
    FUN_00613280();

    bestIndex = -1;
    threshold = DAT_00d8b374; // some constant threshold for target score
    int passCount = 0;
    bool firstPass = (targetMask & 1) != 0; // local_2c

    // Loop over up to 64 target slots (index 0-63)
    do {
        i = 0;
        slotPtr = this + 0x20; // start of slot 1? base for accessing pointer at slot start +4
        do {
            // Get the pointer to the entity for this slot (stored at slot start +4 dwords)
            candidatePointer = *(slotPtr - 0x1c); // equivalent to this[4 + i*0x20]
            if (candidatePointer != 0) {
                if (*(int *)(candidatePointer + 0x90) != 0) { // object has health or state
                    // Check if this target type matches the current mask
                    uint4 typeMask = *slotPtr; // this[0x20 + i*0x20]
                    if ((targetMask & typeMask) != 0) {
                        // Compute score for this target (distance/proximity)
                        score = 0.0f;
                        FUN_00943210(candidatePointer, typeMask, crosshairPos, &score, (passCount != 0));

                        // Handle special cases: type 3 and 6 when targetMask == 2 (maybe injured or downed)
                        if (((typeMask == 3) || (typeMask == 6)) && (targetMask == 2)) {
                            if (score > 0.0f) {
                                score = score + DAT_00d61ae8; // add a bonus for these types
                            }
                        } else {
                            // If score > 0 and type == 6, consider it locked on
                            if ((score > 0.0f) && (typeMask == 6)) {
                                isLockedOn = true;
                                visibilityMask = 2;
                                goto nextSlot; // skip further selection
                            }
                        }

                        // Only consider this target if it's not type 8 (maybe UI only)
                        if ((typeMask & 8) == 0) {
                            if (threshold < score) {
                                bestIndex = i;
                                threshold = score;
                            }
                        }
                    }
                }
            }
nextSlot:
            i++;
            slotPtr += 0x20; // move to next slot (128 bytes apart)
        } while (i < 64);

        if (firstPass == 0) goto donePass; // if firstPass is false, only one pass
        // Repeat if bestIndex remains -1 and we haven't exhausted passes
        passCount++;
    } while ((bestIndex == -1) && (passCount < 2));

    if (firstPass == 0) {
donePass:
        // No sticky targeting on first pass
        this[0x816] = 0xFFFFFFFF; // m_iPreviousTargetId
        this[0x817] = 0xFFFFFFFF; // m_iCurrentTargetId
        this[0x818] = 0;          // m_iTargetLockTimer
        bestIndex = -1;
    }
    else if (passCount != 0) {
        // Second pass: check if previous target is still valid
        prevTargetIndex = this[0x817]; // m_iCurrentTargetId from previous frame
        if ((prevTargetIndex >= 0) &&
            ((this[prevTargetIndex * 0x20 + 4] == 0) ||
             (*(int *)(this[prevTargetIndex * 0x20 + 4] + 0x90) == 0)))
        {
            this[0x817] = 0xFFFFFFFF; // invalidate previous target
        }

        int newTargetIndex = this[0x817];
        if (newTargetIndex < 0) {
            // No sticky target, set sticky parameters
            this[0x819] = 16;          // m_iStickyCount max
            this[0x81a] = bestIndex;   // m_iStickyTargetId
        }
        else {
            // Sticky target exists
            if (this[0x818] < 1) { // lock timer not expired
                if (this[0x81a] == bestIndex) {
                    // Same target: increment sticky counter if below 16
                    if (this[0x819] < 16) {
                        this[0x819] = this[0x819] + 1;
                    }
                    newTargetIndex = prevTargetIndex; // keep old target
                }
                else {
                    // Different target: reset sticky counter
                    this[0x81a] = bestIndex;
                    this[0x819] = 0;
                }
            }
        }
    }
    else {
        // First pass only - no sticky logic
        this[0x81a] = 0xFFFFFFFF;
        this[0x819] = 0xFFFFFFFF;
    }

    bestIndex = newTargetIndex; // iVar5
    if (bestIndex == -1) {
        isLockedOn = false;
        visibilityMask = 2; // fallback
        targetMask = 2;
    }
    else if (this[(bestIndex + 1) * 0x20] == 3) { // check if next type is 3 (maybe other type)
        isLockedOn = true;
    }

    int previousId = this[0x817];
    if (bestIndex != previousId) {
        this[0x816] = previousId;
        this[0x817] = bestIndex;
        if (previousId != -1) {
            this[0x818] = 20; // lock timer
        }
    }

    // Call final target selection function if requested
    if (targetMask == 1) {
        if (bestIndex >= 0) {
            FUN_009434a0(outTargetArray, outTargetCount, crosshairPos, bestIndex, threshold);
        }
    }
    else if (outTargetCount != 0) {
        // Clear output buffer if not using single target mode
        uint4 *clearPtr = (uint4 *)(outTargetArray + 0x20);
        int clearCount = outTargetCount;
        do {
            *clearPtr = 0;
            clearPtr += 12; // clear 48 dwords per target?
            clearCount--;
        } while (clearCount != 0);
    }

    // Second loop: draw target markers or notify entities
    threshold = 0.0f;
    int *slotStart = this + 4; // start of slot array (pointer field)
    do {
        int entityPtr = *slotStart;
        if ((entityPtr != 0) &&
            (*(int *)(entityPtr + 0x90) != 0) &&
            ((visibilityMask & slotStart[0x1c]) != 0) && // slotStart[0x1c] is type mask (at offset 0x20 from slot start?)
            (slotStart[0x1c] != 6) &&
            (((threshold == (float)bestIndex) || (bestIndex == -1)) ||
             (((targetMask & slotStart[0x1c]) != 0) && ((slotStart[0x1c] & 8) != 0))))
        {
            // Notify entity? (function at 0x00433700 probably plays a sound or effect)
            FUN_00433700(*(int *)(entityPtr + 0x90), entityPtr, 0, 0xFFFFFFFF, 1, 0);
        }
        threshold = (float)((int)threshold + 1);
        slotStart += 0x20; // move to next slot
    } while ((int)threshold < 64);

    // Handle lock timer and update debug overlay
    if (this[0x818] > 0) {
        int timer = this[0x818] - 1;
        int prevTarget = this[0x816];
        this[0x818] = timer;
        if (prevTarget >= 0) {
            // Check if previous target is still valid and visible
            if ((this[prevTarget * 0x20 + 4] != 0) &&
                (*(int *)(this[prevTarget * 0x20 + 4] + 0x90) != 0) &&
                ((visibilityMask & this[prevTarget * 0x20 + 0x20]) != 0) &&
                (this[prevTarget * 0x20 + 0x20] != 6))
            {
                // Update debug overlay variables (global colors)
                if (DAT_012058d0 < 0x1b) DAT_012058d0 = 0x1b;
                if (DAT_00f15988 > 0x1b) DAT_00f15988 = 0x1b;
                _DAT_011f3cdc = ((timer * 0xff) / 20) & 0xff;
                _DAT_011f3cdc = ((_DAT_011f3cdc << 8 | _DAT_011f3cdc) << 8 | _DAT_011f3cdc) << 8 | _DAT_011f3cdc;
                _DAT_011f3a44 = 1;
                if (DAT_012058d4 < 0xc1) DAT_012058d4 = 0xc1;
                if (DAT_00f1598c > 0xc1) DAT_00f1598c = 0xc1;
                FUN_00417cf0(1, 0xe, 0xf);
                // Set more debug values
                if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
                if (DAT_00f15988 > 0x19) DAT_00f15988 = 0x19;
                _DAT_011f3a3c = 5;
                if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
                if (DAT_00f15988 > 0x18) DAT_00f15988 = 0x18;
                _DAT_011f3a38 = 0;
                if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
                if (DAT_00f15988 > 0xf) DAT_00f15988 = 0xf;
                _DAT_011f3a14 = 0;

                // Get pointer of previous target
                uint4 prevEntity = 0;
                if (this[prevTarget * 0x20 + 4] != 0) {
                    prevEntity = *(uint4 *)(this[prevTarget * 0x20 + 4] + 0x90);
                }
                FUN_00433700(prevEntity, this[prevTarget * 0x20 + 4], 0, 0xFFFFFFFF, 2, 0);
                FUN_00417cf0(1, 5, 6);
                // More debug overlay updates...
                // ... (similar pattern repeated)
                if (DAT_012058d0 < 0x1b) DAT_012058d0 = 0x1b;
                if (DAT_00f15988 > 0x1b) DAT_00f15988 = 0x1b;
                _DAT_011f3a44 = 0;
                if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
                if (DAT_00f15988 > 0x19) DAT_00f15988 = 0x19;
                _DAT_011f3a3c = 7;
                if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
                if (DAT_00f15988 > 0x18) DAT_00f15988 = 0x18;
                _DAT_011f3a38 = 0;
                if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
                if (DAT_00f15988 > 0xf) DAT_00f15988 = 0xf;
                _DAT_011f3a14 = 0;
            }
        }
    }

    // Finalize rendering
    FUN_00434aa0(*this, 0xd, 0x17);
    FUN_00434b90(*this);
    FUN_00613570(7);
    FUN_00609890(1);
    FUN_0060dcb0();
    textureHandle = FUN_0060d860(0);
    FUN_006094e0(textureHandle);

    if (contextA != 0) {
        FUN_00422900();
    }
    if (contextB != 0) {
        FUN_00423410();
    }

    // Write result to output buffer (for debug overlay)
    int *outPtr = (int *)(DAT_012068e8 + 0x14);
    **(int **)(DAT_012068e8 + 0x14) = (int)&PTR_FUN_00e56938;
    *outPtr = *outPtr + 4;
    *(*outPtr) = outTargetCount;
    *outPtr = *outPtr + 4;
    *(*outPtr) = 0x10;
    *outPtr = *outPtr + 4;
    FUN_0049c430(outTargetArray, outTargetCount * 0x30, 0x10);
    *(*outPtr) = isLockedOn;
    *outPtr = *outPtr + 4;

    return;
}