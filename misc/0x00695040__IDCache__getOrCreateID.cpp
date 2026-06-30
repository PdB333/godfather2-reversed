// FUNC_NAME: IDCache::getOrCreateID
void __thiscall IDCache::getOrCreateID(int thisTable, int *outPair, int key) {
    int computedID; // eax
    int *pairPtr; // piVar2
    int local_data[2]; // used for pair construction

    computedID = hashFunction(key);
    if (thisTable == 0) {
        debugBreak();
    }
    // Check if the computed ID matches the cached current ID
    if (computedID != *(int *)(thisTable + 4)) {
        // Try to allocate/validate the slot at (computedID + 0xC)
        computedID = allocateSlot(computedID + 0xC);
        if (computedID >= 0) {
            // Allocation succeeded: use the computed hash as the result
            outPair[0] = thisTable;
            outPair[1] = *(int *)(&local_data[0] + 1); // This is actually local_data[-0xC]?? Wait, we need to be careful.
        }
    } else {
        // Computed ID matches cached value: return the cached ID
        outPair[0] = thisTable;
        outPair[1] = *(int *)(thisTable + 4);
    }
    // Note: if allocation fails (iVar1 < 0) the code path is undefined, likely crashes.
    // The above reconstruction approximates the logic.
}