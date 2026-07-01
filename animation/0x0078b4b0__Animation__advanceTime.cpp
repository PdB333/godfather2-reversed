// FUNC_NAME: Animation::advanceTime

void __thiscall Animation::advanceTime(int this, float deltaTime, bool isReverse, bool bApplyEndCallback)
{
    float fVar1;
    bool bIsForward;
    bool bTriggerEvents;
    bool bAtEnd;
    float* pfVar5;
    uint uVar6;
    uint uVar11;
    int iVar7;
    uint* puVar8;
    float fVar9;
    float fVar10;
    float local_1c;
    float local_18;
    float local_14;
    undefined1 auStack_10[4];
    int aiStack_c[3];

    // Check if animation is active
    if (!isAnimationActive()) {
        return;
    }

    // Ignore negligible time deltas
    if (deltaTime < g_MinAnimationDelta) {
        return;
    }

    // Save current animation time at +0x40
    fVar10 = *(float*)(this + 0x40);
    local_14 = fVar10;

    // Determine direction and speed modifiers
    bIsForward = isAnimPlayingForward();
    fVar9 = *(float*)(this + 0x54); // base speed/scale
    if ((**(int**)(DAT_012233a0 + 4) != 0) && (**(int**)(DAT_012233a0 + 4) != 0x1f30)) {
        // Global game object (e.g. player) exists; compute velocity-adjusted speed
        fVar9 = (fVar9 + *(float*)(this + 0x58)) * g_GlobalSpeedFactor;
        fVar9 = fVar9 - (*(float*)(this + 0x58) - fVar9);
        if (fVar9 < 0.0f) {
            fVar9 = 0.0f;
        }
    }

    bTriggerEvents = shouldTriggerEvents();

    // Handle direction (reverse vs forward)
    if (!isReverse) {
        if (bIsForward) {
            // Set playback speed and get time range for interpolation
            setGlobalSpeedFactor(DAT_00d5c458);
            getAnimationTimeRange(&local_1c, &local_18);
            // Interpolate deltaTime based on progress in the animation
            deltaTime = (g_AnimationEndTime - (*(float*)(this + 0x40) - local_1c) / (local_18 - local_1c)) * deltaTime;
        }
        // Accumulate forward time at +0x48
        *(float*)(this + 0x48) += deltaTime;
        updateWorldTransform();
    } else {
        // Reverse direction: override deltaTime with speed multiplier from global
        iVar7 = **(int**)(DAT_012233a0 + 4);
        if ((iVar7 != 0) && (iVar7 != 0x1f30)) {
            deltaTime = *(float*)(iVar7 + 0x1e0) * deltaTime;
        }
        // Accumulate reverse time at +0x44
        *(float*)(this + 0x44) += deltaTime;
    }

    // Clamp main animation time (+0x40) between 0 and max
    local_18 = fVar10 + deltaTime;
    float fMaxTime = DAT_00d5e288;
    local_14 = 0.0f;
    if (local_18 <= DAT_00d5e288) {
        pfVar5 = &local_14;
        if (0.0f <= local_18) {
            pfVar5 = &local_18;
        }
    } else {
        pfVar5 = &fMaxTime;
    }
    fVar1 = *pfVar5;
    *(float*)(this + 0x40) = fVar1;

    // Trigger events when crossing thresholds
    if (bTriggerEvents) {
        if (g_EventThreshold < fVar1 - *(float*)(this + 0x4c)) {
            // Crossing a significant progress boundary: fire event
            onAnimationEvent(*(int*)(this + 0x5c), this, deltaTime);
        }
        bAtEnd = isAnimationAtEnd();
        if ((bAtEnd) && ((*(uint*)(*(int*)(*(int*)(this + 0x5c) + 0x2124) + 0x20) >> 8 & 1) == 0)) {
            // At end and certain flags not set: play end sound and set state
            playSound(&DAT_0112afc8);
            setAnimationFlag(1);
            setAnimationState(this, 1);
        }
    }

    // Handle speed clamping and additional state transitions
    if (fVar9 <= fVar10) {
        if (!bIsForward) goto LAB_0078b7c3;
    } else {
        bIsForward = isAnimPlayingForward();
        if (bIsForward) {
            // Entering a speed-limited zone: play sound and set flag
            if ((*(byte*)(*(int*)(this + 0x5c) + 0x1f98) & 0x11) == 0) {
                pushSoundContext(0, 0);
                postSoundEvent(0x832a6bae, 0x74, uVar6, 0);
                popSoundContext();
                updateSound();
            }
            puVar8 = (uint*)(*(int*)(this + 0x5c) + 0x1f58);
            *puVar8 |= 0x20000000;
            if (bTriggerEvents) {
                playSound(&DAT_0112afc0);
                setAnimationState(this, 2);
            }
            goto LAB_0078b7c3;
        }
    }

    // Check for blending/transition condition
    if (isAnimationBlending()) {
        if (bTriggerEvents) {
            playSound(&DAT_0112afd0);
            setAnimationState(this, 3);
        }
        // Apply flag on linked object if condition holds
        if (((*(uint*)(*(int*)(this + 0x5c) + 0x1f54) >> 8 & 1) != 0) &&
            (iVar7 = getLinkedCharacter(*(int*)(*(int*)(this + 0x5c) + 0x2134)), iVar7 != 0)) {
            puVar8 = (uint*)(*(int*)(iVar7 + 0x180) + 0x34);
            *puVar8 |= 0x2000000;
        }
        // Clear the speed-limited flag
        puVar8 = (uint*)(*(int*)(this + 0x5c) + 0x1f58);
        *puVar8 &= 0xdfffffff;
    }

LAB_0078b7c3:
    // Final apply: push animation to character if requested and not already at final frame
    if ((!isAtFinalFrame()) && (bApplyEndCallback)) {
        applyAnimationToCharacter(*(int*)(this + 0x5c));
        pushDebugMessage(&DAT_0112afe0, auStack_10, 0);
        if (aiStack_c[0] != 0) {
            debugOutput(aiStack_c);
        }
    }
    return;
}