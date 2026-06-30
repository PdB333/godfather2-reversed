// FUNC_NAME: PlayerActionableTargetSM::updateState

void __fastcall PlayerActionableTargetSM::updateState(PlayerActionableTargetSM* thisPtr)
{
    // +0xF0: targetEntity (pointer to some entity)
    // +0xF4: flag something (maybe "isInCover")
    // +0xF8: some integer state
    // +0xFC: active flag (if zero, skip all)
    // +0x100: animationStatePtr1 (maybe "idleAnimationState")
    // +0x108: animationStatePtr2 (maybe "interactionAnimationState")

    bool bAnyInvalid;
    bool bStateInvalid;
    bool bMemoryPressure;
    int entityPtr;
    int* animState1;
    int* animState2;
    int* derivedObj;
    int* derivedObj2;
    int temp;
    uint flags;

    // Quick exit if not active
    if (*(char*)(thisPtr + 0xFC) == '\0')
        return;

    animState1 = (int*)(thisPtr + 0x100);
    animState2 = (int*)(thisPtr + 0x108);

    // Check if either animation state pointer is NULL or has sentinel value 0x48
    bAnyInvalid = false;
    if ((*animState1 == 0) || (*animState1 == 0x48) ||
        (*animState2 == 0) || (*animState2 == 0x48))
    {
        bAnyInvalid = true;
    }

    // Check if state machine is in an invalid interaction state
    if ((*animState2 == 0) || (*animState2 == 0x48) || (FUN_00706c20() != 0))
    {
        bStateInvalid = false;
    }
    else
    {
        bStateInvalid = true;
    }

    // Check memory pressure (heap allocation success)
    entityPtr = *(int*)(thisPtr + 0xF0);
    if ((entityPtr != 0) && (entityPtr != -0x2744))
    {
        // 0x20000 likely a pool flag
        int memToken = FUN_007e04a0(0x20000);
        int availSize = FUN_007e0790(memToken);
        if ((availSize != 0) && (availSize < 0x8000000))
        {
            bMemoryPressure = true;
            goto checkAndClear;
        }
    }
    bMemoryPressure = false;

checkAndClear:
    // If any condition indicates we should abort the current interaction
    if (bAnyInvalid || bStateInvalid || bMemoryPressure)
    {
        *(char*)(thisPtr + 0xFC) = 0;  // deactivate
        // Free animation state objects
        if (*animState1 != 0)
        {
            FUN_004daf90(animState1);  // likely operator delete
            *animState1 = 0;
        }
        if (*animState2 != 0)
        {
            FUN_004daf90(animState2);
            *animState2 = 0;
        }
        FUN_0090bb90(0);  // trigger some global cleanup
    }
    else
    {
        // Allocate a temporary object (size 0x34) for animation data
        int* tempObj = (int*)FUN_00798f50(0x34);
        char allocSuccess = FUN_0079e970(tempObj);  // initialize? returns bool

        if (allocSuccess != 0)
        {
            *(char*)(thisPtr + 0xFC) = 0;  // deactivate (will be reactivated later?)
            FUN_0090bb90(0);

            // Get the derived object from animState2 (subtract 0x48 to get base)
            if (*animState2 == 0)
                derivedObj = 0;
            else
                derivedObj = (int*)(*animState2 - 0x48);

            // Check bit 4 of flags at +0x1D0 in derivedObj
            if ((*(uint*)(derivedObj + 0x1D0) >> 4 & 1) == 0)
            {
                // No bit4 set: handle via main entity path
                // Check global entity's bit4
                if ((*(uint*)(*(int*)(thisPtr + 0xF0) + 0x8E0) >> 10 & 1) != 0)
                {
                    int globalEntity = FUN_00691810();  // get singleton
                    if ((*(uint*)(globalEntity + 0x1D0) >> 4 & 1) == 0)
                        globalEntity = 0;
                    FUN_0079d9c0(globalEntity);  // clear something
                }

                if (*animState2 == 0)
                    derivedObj = 0;
                else
                    derivedObj = (int*)(*animState2 - 0x48);
                FUN_00690820(derivedObj);  // reset animation?

                if (*animState2 == 0)
                    animState1 = (int*)0x0;
                else
                    animState1 = (int*)(*animState2 - 0x48);
                // Call vfunc at offset 0x174 on derivedObj, passing entity at +0xF0
                (**(code**)(*animState1 + 0x174))(*(uint*)(thisPtr + 0xF0));
                return;
            }
            else
            {
                // Bit4 set: handle via animState1 path
                if (*animState1 == 0)
                    derivedObj = 0;
                else
                    derivedObj = (int*)(*animState1 - 0x48);
                FUN_00704360(derivedObj);  // stop current animation?

                if (*animState1 == 0)
                    derivedObj2 = (int*)0x0;
                else
                    derivedObj2 = (int*)(*animState1 - 0x48);
                // Call vfunc at offset 0x170 (fade, blend)
                (**(code**)(*derivedObj2 + 0x170))(0, 0x1FF, 1, 0x3F800000, 0);

                // More cleanup functions
                if (*animState2 == 0)
                    derivedObj = 0;
                else
                    derivedObj = (int*)(*animState2 - 0x48);
                FUN_00704ca0(derivedObj);

                if (*animState2 == 0)
                    derivedObj = 0;
                else
                    derivedObj = (int*)(*animState2 - 0x48);
                FUN_00704590(derivedObj);

                FUN_00707ea0();  // global state?
                FUN_00707610();  // another global?

                // Conditional face animation
                if (*animState2 == 0)
                    derivedObj = 0;
                else
                    derivedObj = (int*)(*animState2 - 0x48);
                if (*(char*)(derivedObj + 0x1A8) == '\x01')
                {
                    if (*animState2 == 0)
                        derivedObj = 0;
                    else
                        derivedObj = (int*)(*animState2 - 0x48);
                    uint faceFlags = FUN_007014d0(0);
                    if ((*(char*)(thisPtr + 0xF4) == '\0') &&
                        ((*(uint*)(derivedObj + 0x2D8) >> 6 & 1) == 0))
                    {
                        faceFlags = faceFlags & 0xFFFFFF00; // clear lower byte
                    }
                    else
                    {
                        faceFlags = 1;
                    }
                    FUN_007046a0(faceFlags); // set face animation
                }

                // Check if we should hand off to global entity
                int globalEntity = FUN_00691810();
                if (globalEntity != 0)
                {
                    if (*animState1 == 0)
                        derivedObj2 = 0;
                    else
                        derivedObj2 = (int*)(*animState1 - 0x48);
                    if (derivedObj2 == (int*)globalEntity)
                    {
                        if (*animState2 == 0)
                            derivedObj = 0;
                        else
                            derivedObj = (int*)(*animState2 - 0x48);
                        FUN_00704c10(derivedObj); // sync?

                        if (*animState2 == 0)
                            derivedObj = 0;
                        else
                            derivedObj = (int*)(*animState2 - 0x48);
                        // Call vfunc at offset 600 (0x258) on entity at +0xF0, passing derivedObj
                        (**(code**)(**(int**)(thisPtr + 0xF0) + 600))(derivedObj);

                        if (*animState2 == 0)
                            derivedObj = 0;
                        else
                            derivedObj = (int*)(*animState2 - 0x48);
                        FUN_00690820(derivedObj);
                    }
                }

                // Finalize with vfunc 0x174 again
                if (*animState2 == 0)
                    animState1 = (int*)0x0;
                else
                    animState1 = (int*)(*animState2 - 0x48);
                (**(code**)(*animState1 + 0x174))(*(uint*)(thisPtr + 0xF0));

                // Check if we need to store state at +0xF8
                char isOngoing = FUN_00705b40();
                if (isOngoing == 0)
                {
                    if (*animState2 == 0)
                        derivedObj = 0;
                    else
                        derivedObj = (int*)(*animState2 - 0x48);
                    uint newState = FUN_00704860(derivedObj);
                    *(uint*)(thisPtr + 0xF8) = newState;

                    if (*animState2 == 0)
                        derivedObj = 0;
                    else
                        derivedObj = (int*)(*animState2 - 0x48);
                    (**(code**)(**(int**)(thisPtr + 0xF0) + 600))(derivedObj);
                    return;
                }
            }
        }
    }
    return;
}