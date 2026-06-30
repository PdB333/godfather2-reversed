// FUNC_NAME: AnimationManager::updateAnimationState (0x00432e30)
void AnimationManager::updateAnimationState(int contextBase)
{
    // in_EAX holds the instance index (animation slot) - typically passed via EAX register
    int instanceIndex = in_EAX; 
    int animDataOffset = instanceIndex * 0x6A0 + 0x1230 + contextBase; // base of per-instance animation data

    int currentAnimIndex = *(short*)(this + 0x2A); // current animation index (e.g., from character state)
    uint flags = *(uint*)(this + 0x08);            // animation flags (e.g., movement, combat, etc.)

    // Data read from the animation instance tables (stride 0x20 and 0x10)
    undefined4 animData1 = 0;
    undefined4 animData2 = 0;
    undefined4 vecBuffer[4]; // 16-byte buffer for vector/quaternion
    short extraShort = 0;

    if (currentAnimIndex >= 0) {
        int ptrTable1 = currentAnimIndex * 0x20 + *(int*)(animDataOffset + 0x10);
        animData1 = *(undefined4*)(ptrTable1 + 0x0C);
        animData2 = *(undefined4*)(ptrTable1 + 0x1C);

        int* ptrTable2 = (int*)(currentAnimIndex * 0x10 + *(int*)(animDataOffset + 4));
        vecBuffer[0] = *(undefined4*)ptrTable2;
        vecBuffer[1] = *(undefined4*)(ptrTable2 + 1);
        vecBuffer[2] = *(undefined4*)(ptrTable2 + 2);
        vecBuffer[3] = *(undefined4*)(ptrTable2 + 3);

        extraShort = *(short*)(*(int*)(animDataOffset + 0x0C) + currentAnimIndex * 2);
    }

    FUN_004c4e60(); // likely a per-frame update or cleanup (e.g., blending weight calculation)

    // Determine animation state (uVar6) based on flags and internal counters
    uint animState = flags;
    if (flags & 0x20) {
        animState = 6; // e.g., dead/stunned
    } else if (flags & 0x0C) {
        animState = 3; // e.g., mid-air or falling
    } else {
        if (*(char*)(this + 0x28) < 1) {
            if (*(char*)(this + 0x04) == 1 || (flags & 0x10)) {
                animState = 1; // e.g., idle
            } else if (flags & 0x8000) {
                animState = 5; // e.g., transition/interrupt
            } else {
                animState = (flags >> 0x0E) & 4; // 0 or 4
            }
        } else {
            animState = 2; // e.g., moving
        }
    }

    *(char*)(this + 0x29) = (char)animState; // store current animation state

    // Dispatch to animation playback function based on computed state
    switch (animState) {
    case 0:
    case 1:
    case 4:
        FUN_004c4ba0(this, animData1, (undefined4*)vecBuffer, extraShort, 0);
        break;
    case 2: {
        int blendFactor = *(char*)(this + 0x28);
        if (blendFactor == 0)
            blendFactor = 1;
        FUN_004c4ba0(this, animData1, (undefined4*)vecBuffer, extraShort, blendFactor);
        goto LAB_00432f1f;
    }
    case 5:
        FUN_004c4ba0(this, animData1, (undefined4*)vecBuffer, extraShort, 0);
        // Callback after specific animation state (e.g., completion or transition)
        if (*(code**)(contextBase + 0x3A24) != (code*)0x0) {
            (**(code**)(contextBase + 0x3A24))((undefined4*)(contextBase + 0x3A10));
        } else {
            (**(code**)(contextBase + 0x3A10))();
        }
        return;
    }

    // For states 0 or 2, write back animation data (e.g., final pose/quaternion)
    if (animState == 0 || animState == 2) {
LAB_00432f1f:
        int* targetArray = (int*)(contextBase + 0x1240 + animState * 0x6A0);
        int writeOffset = *(int*)(targetArray) + 0x1C + *(short*)(this + 0x2A) * 0x20;
        *(undefined4*)(writeOffset) = animData2;
    }
    return;
}