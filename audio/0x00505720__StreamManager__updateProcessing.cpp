// FUNC_NAME: StreamManager::updateProcessing
void StreamManager::updateProcessing(StreamManager* thisPtr, int* pRingBufferState)
{
    // Call base/debug function
    FUN_00533cc0();

    // Set vtable pointer for this object (likely derived class)
    thisPtr->vtable = &PTR_FUN_00e37fe0;

    if (*(char*)(pRingBufferState + 0xd) == '\0') {
        // Initialize ring buffer indices
        thisPtr->field9 = pRingBufferState;
        thisPtr->field10 = 0;

        uint hashId = 0;
        if ((pRingBufferState[0] != 0 || pRingBufferState[1] != 0) ||
            (pRingBufferState[2] != 0 || pRingBufferState[3] != 0)) {
            hashId = FUN_004e9270();  // Get hash or unique ID
            if ((hashId != 0) &&
                ((hashId != 0xffffffff && (hashId < 0x1000)) && (hashId * 0x38 != -0x11a0f28))) {
                // Increment reference count in resource table
                int** ppEntry = (int**)(&DAT_011a0f38 + hashId * 0x38);
                if (*ppEntry != nullptr) {
                    **ppEntry = **ppEntry + 1;
                }
            }
        }

        uint valA = thisPtr->field1;
        uint valB = *(uint*)(pRingBufferState + 8);

        int idx1 = DAT_0119478c - 1;
        int idx2 = DAT_0119478c + 2;
        if (idx1 < 0) {
            idx1 = 0x13;  // Wrap to last element (size 20)
        }
        else if (0x13 < idx2) {
            idx2 = DAT_0119478c - 0x12;  // Wrap idx2
        }

        // Update ring buffer sum (running total)
        DAT_01194790[idx1] = DAT_01194790[idx1] + DAT_01194790[idx2];
        DAT_0119478c = idx1;

        // Call processing function with multiple parameters
        FUN_005054a0(
            thisPtr,
            *(undefined4*)(thisPtr->field1 + 0x10),
            CONCAT44(valA, pRingBufferState),
            CONCAT44(DAT_01194790[idx1], valB),
            hashId,
            thisPtr->field4,
            thisPtr->field5
        );
    }
}