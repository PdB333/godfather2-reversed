// FUNC_NAME: ActionController::getActionDuration

int __fastcall ActionController::getActionDuration(int thisPtr) // this in ecx
{
    float fVar1;
    float fVar2;
    char cVar3;
    int iVar4;
    int iVar5;
    int returnVal;
    int timeBase;

    *(int *)(thisPtr + 0xCC) = 0; // mCalculatedDuration = 0

    // Check if action pointer at +0x40 is valid
    if ((*(int *)(thisPtr + 0x40) != 0) &&
        // Check if the action is active (FUN_008c74d0 likely returns non-zero if valid)
        (iVar4 = isActionValid(*(int *)(thisPtr + 0x40)), iVar4 != 0))
    {
        // +0xC4 likely stores a timer mode (0 = simple, 1 = animation-based)
        if (*(int *)(thisPtr + 0xC4) == 0)
        {
            // Simple random duration: get base time from RNG, apply multiplier
            iVar4 = getBaseTime(); // FUN_008bece0
            fVar1 = (float)iVar4;
            if (iVar4 < 0)
            {
                fVar1 = fVar1 + DAT_00e44578; // float adjustment for signed conversion
            }
            // +0xD0 is a duration multiplier
            timeBase = (int)(fVar1 * *(float *)(thisPtr + 0xD0));
            *(int *)(thisPtr + 0xCC) = timeBase;
            return timeBase;
        }

        // Timer mode 1: animation-based duration
        if (((*(int *)(thisPtr + 0xC4) == 1) && 
             (*(int *)(thisPtr + 0xC0) != 0)) && // +0xC0 points to animation data
            // Check game state (likely pause flag or global condition)
            (iVar4 = isGameReady(), iVar4 != 0) && // FUN_0084a410
            // Check character state (alive/active?)
            (cVar3 = isCharacterAlive(), cVar3 != '\0')) // FUN_0084a670
        {
            // Get animation duration from vtable at +0xC0
            iVar4 = **(int **)(thisPtr + 0xC0) + 4; // accesses vtable entry at index 1
            iVar5 = getAnimationDuration(); // FUN_0084a5b0, returns float as int
            fVar1 = (float)iVar5;
            if (iVar5 < 0)
            {
                fVar1 = fVar1 + DAT_00e44578;
            }
            fVar2 = (float)iVar4;
            if (iVar4 < 0)
            {
                fVar2 = fVar2 + DAT_00e44578;
            }
            // Ratio of animation duration / vtable duration? But calls are same:
            // Actually two calls to getAnimationDuration, one unused result
            if (fVar1 / fVar2 <= 0.0)
            {
                getAnimationDuration(); // possibly side effect
            }
            else
            {
                getAnimationDuration();
            }
            // Final calculated duration from some other source
            returnVal = calculateFinalDuration(); // FUN_00b9a1c0
            *(int *)(thisPtr + 0xCC) = returnVal;
        }
    }
    return *(int *)(thisPtr + 0xCC); // return current value (0 if no action)
}