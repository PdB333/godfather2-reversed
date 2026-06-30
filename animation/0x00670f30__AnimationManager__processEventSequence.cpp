// FUNC_NAME: AnimationManager::processEventSequence
// 0x00670f30
// Processes a sequence of animation event IDs (shorts) for a given animation slot.
// slotIndex: index into the animation slot table (each entry 20 bytes, at offset 0x28 from manager base)
// manager: pointer to AnimationManager instance (contains a pointer at +0x8 to an indirect animation state)
// eventList: null-terminated array of event IDs (2-byte shorts)
// Returns: a computed animation progress value (frames/time)
int __thiscall AnimationManager::processEventSequence(int slotIndex, AnimationManager* manager, short* eventList)
{
    int* pAnimStateIndirect;       // pointer to indirect animation state pointer (from manager+0x8)
    short* pCurrentEvent;          // current event pointer
    short* pTableEntry;            // pointer to the short in the slot table entry
    int basePtr;                   // mutable base pointer (initially manager, then indirect state)
    short eventCheckResult;        // result from checkAnimationEvent
    int progressValue;             // computed animation progress
    uint eventIdx;                 // loop counter (masked to 16-bit)
    int outputAccumulator;         // output accumulator written by processAnimationEvent
    short* pEventWalker;           // copies eventList for walking

    basePtr = (int)manager;        // treat manager as base integer
    progressValue = 0;
    eventIdx = 0;
    outputAccumulator = 0;         // local output accumulator
    pEventWalker = eventList;

    if (*eventList != 0)
    {
        // slot table location: manager + (slotIndex * 5 + 10) * 4
        // Each slot occupies 5 integers (20 bytes), table starts at offset 0x28 (40 bytes)
        pTableEntry = (short*)((int)manager + (slotIndex * 5 + 10) * 4);
        pAnimStateIndirect = (int*)((int)manager + 8);  // pointer to indirect state pointer

        do
        {
            pCurrentEvent = eventList + (eventIdx & 0xFFFF);
            eventCheckResult = checkAnimationEvent(*pTableEntry, pAnimStateIndirect, eventList[eventIdx & 0xFFFF]);

            if (eventCheckResult == 0)
            {
                processAnimationEvent(*pTableEntry, pAnimStateIndirect, *pCurrentEvent, globalAnimationData, &outputAccumulator);
            }

            // Dereference the indirect pointer to get actual animation state object
            basePtr = *pAnimStateIndirect;

            // Calculate progress: (state[0xe4] + (outputAccumulator >> 10) >> 6) + state[0x10c]
            progressValue = (*(int*)(basePtr + 0xe4) + (outputAccumulator >> 10) >> 6) + *(int*)(basePtr + 0x10c);

            // If flag at offset 0x64 (+100) is non-zero, accumulate delta at 0xd0
            if (*(int*)(basePtr + 100) != 0)
            {
                outputAccumulator += *(int*)(basePtr + 0xd0);
            }

            pEventWalker++;
            eventIdx++;
        } while (*pEventWalker != 0);
    }

    return progressValue;
}