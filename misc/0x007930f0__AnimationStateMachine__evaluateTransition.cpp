// FUNC_NAME: AnimationStateMachine::evaluateTransition
int __thiscall AnimationStateMachine::evaluateTransition(int thisPtr, int stateIndex, int *outTransitionId)
{
    int *stateEntry;
    int *stateFlags;
    int result;
    undefined4 animHandle;

    // Each state entry is 0x1c bytes. Base offset 0x50 for state array.
    stateEntry = (int *)(thisPtr + 0x50 + stateIndex * 0x1c);
    stateFlags = stateEntry + 5; // +0x14: flags field

    *outTransitionId = 0;

    // Check if state is not active or is a special "idle" state (0x48)
    if (((*stateFlags == 0) || (*stateFlags == 0x48)) &&
        // Check if state has any animation data (not all zeros)
        ((*stateEntry != 0 || (((stateEntry[1] != 0 || (stateEntry[2] != 0)) || (stateEntry[3] != 0)))) &&
        // Check if state is not a "null" sentinel value (-0x45245246, -0x41104111, -0x153ea5ab, -0x6eeff6ef)
        ((*stateEntry != -0x45245246 || (stateEntry[1] != -0x41104111)) ||
         ((stateEntry[2] != -0x153ea5ab || (stateEntry[3] != -0x6eeff6ef))))))
    {
        // State is inactive or idle, but has animation data that is not null sentinel
        // Call some animation processing function
        animHandle = FUN_00446100(stateEntry, 0);
        FUN_00726830(animHandle);
    }

    if ((*stateFlags != 0) && (*stateFlags != 0x48))
    {
        // State is active and not idle
        result = *stateFlags;
        if (result != 0)
        {
            *outTransitionId = stateEntry[4]; // +0x10: transition ID
            return result - 0x48; // Return adjusted state type
        }
        *outTransitionId = stateEntry[4]; // +0x10: transition ID
        return 0;
    }
    return 0;
}