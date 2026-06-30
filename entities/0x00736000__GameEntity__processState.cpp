// FUNC_NAME: GameEntity::processState
void __fastcall GameEntity::processState(int thisPtr)
{
    // Check if bit 0x4000000 (bit 26) is already set at offset +0x1f58
    if ((*(uint *)(thisPtr + 0x1f58) & 0x4000000) == 0) {
        // Set the bit to indicate processing is in progress
        *(uint *)(thisPtr + 0x1f58) |= 0x4000000;

        // Gather member offsets for event dispatch
        int eventArg1 = thisPtr + 0x213c;   // +0x213c: some state or context pointer
        int eventArg2 = thisPtr + 0x214c;   // +0x214c: another state variable
        int eventArg3 = *(int *)(thisPtr + 0x216c); // +0x216c: an int value (e.g. ID)
        int eventArg4 = thisPtr;            // the object itself

        // Dispatch an event with a specific hash (0x369ac561)
        // Likely a notification or state machine trigger
        triggerEvent(0x369ac561, eventArg1, eventArg2, eventArg3, eventArg4);

        // Check condition using the same parameters
        char conditionResult = checkCondition(eventArg1, eventArg2, eventArg3, eventArg4);
        if (conditionResult == '\0') {
            // Condition failed – invoke a completion/cleanup routine on a sub-object at +0x3c
            finishRoutine(thisPtr + 0x3c);
            return;
        }

        // If condition succeeds, examine another member at +0x2178
        int extraFlag = *(int *)(thisPtr + 0x2178);
        if (extraFlag != 0 && extraFlag != 0x48) {
            // Trigger a global system function using the global DAT_01131010
            globalSystemFunction(*(int *)0x01131010);
            // Set some global flag to 1
            setGlobalFlag(1);
        }
    }
    // If bit was already set, do nothing
}