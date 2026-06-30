// FUNC_NAME: EventManager::processPendingQueue
void __thiscall EventManager::processPendingQueue(int thisPtr) // actually param_1 is this pointer
{
    char cVar1;
    int iVar2;
    int index;
    uint32_t *pEvent;

    index = 0;
    // Check if there are pending events (count at +0x1c08)
    if (0 < *(int *)(thisPtr + 0x1c08)) {
        pEvent = (uint32_t *)(thisPtr + 0x1408); // Array of event IDs (or handles) starting at +0x1408
        do {
            // Some global or context check? Returns nonzero if something is active
            cVar1 = FUN_005a3fc0(); 
            if (cVar1 != '\0') {
                iVar2 = FUN_005a3e80(); // Returns a pointer or handle
                if (*(int *)(iVar2 + 0x10) == -1) { // Check if something is invalid
                    FUN_005b9340(); // Possibly an error or reset function
                }
            }
            // Dispatch event via function pointer table at DAT_0103aee0
            // Index is low 15 bits of the event handle stored in pEvent
            (**(code **)(&DAT_0103aee0 + ((uint)*pEvent & 0x7fff) * 4))((uint *)*pEvent);
            index = index + 1;
            pEvent = pEvent + 1;
        } while (index < *(int *)(thisPtr + 0x1c08));
        // Clear count after processing all events
        *(int *)(thisPtr + 0x1c08) = 0;
        return;
    }
    // If no events, just set count to 0
    *(int *)(thisPtr + 0x1c08) = 0;
    return;
}