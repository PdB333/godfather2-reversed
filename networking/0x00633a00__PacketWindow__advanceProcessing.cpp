// FUNC_NAME: PacketWindow::advanceProcessing

// Reconstructed from 0x00633a00. This function handles internal state advancement for a packet sequence window,
// likely part of the TNL networking layer (32-slot windows, sequence/ACK). It checks flags, manages a queue of
// sequence numbers, and invokes external callbacks (FUN_00635d00, FUN_00632ae0).

void __thiscall PacketWindow::advanceProcessing(void) {
    // +0x30: flags (bit3 = windowActive, bit2 = initialized)
    uint8_t flags = *(uint8_t*)((uint)this + 0x30);

    // +0x38: currentSeq, +0x34: nextSeq
    if ((flags & 0x08) && (*(int*)((uint)this + 0x38) == 0)) {
        // Window is active but currentSeq is zero – set it from nextSeq and reset
        *(int*)((uint)this + 0x38) = *(int*)((uint)this + 0x34);
        FUN_00635d00(0xFFFFFFFF); // reset sequence handler
        return;
    }

    if (!(flags & 0x04)) {
        // Not initialized – nothing to do
        return;
    }

    // +0x14: pointer to iterator state (struct with fields: basePtr, ?, ?, current, endPtr)
    int* iterState = *(int**)((uint)this + 0x14);

    // Array header is at basePtr[-4], read fields at +0x0C and +0x14
    int arrayHeader = *(int*)(*(int*)iterState[0] - 4); // header pointer
    int arrayBase = *(int*)(arrayHeader + 0x0C); // base offset of sequence numbers
    int* arrayData = *(int**)(arrayHeader + 0x14); // pointer to actual sequence array

    int nextSeq;
    if (arrayData == 0) {
        nextSeq = 0;
    } else {
        // Compute index: (endPtr - base) >> 2
        int index = (iterState[4][0] - arrayBase) >> 2;
        // arrayData[-1 + index] (due to -4 offset)
        nextSeq = *(int*)((int)arrayData - 4 + index * 4);
    }

    // +0x32: char flag, possibly "processingActive"
    if (*(char*)((uint)this + 0x32) == 0) {
        FUN_00632ae0(); // abort processing
        return;
    }

    // Check if only one element remains in the queue
    uint* endPtr = (uint*)iterState[4];
    if ((int)(*endPtr - arrayBase) >> 2 == 1) {
        iterState[3] = *endPtr; // set current to that single value
    }

    // If current < end, try to advance
    if ((uint)iterState[3] < *endPtr) {
        int currentSeq;
        if (arrayData == 0) {
            currentSeq = 0;
        } else {
            int idx = (iterState[3] - arrayBase) >> 2;
            currentSeq = *(int*)((int)arrayData - 4 + idx * 4);
        }
        if (nextSeq == currentSeq) {
            goto resetCurrent;
        }
    }

    // Process next sequence
    FUN_00635d00(nextSeq);

    // Re-fetch iterator state (may have changed)
    iterState = *(int**)((uint)this + 0x14);

resetCurrent:
    // Reset current to the end pointer value
    iterState[3] = *iterState[4];
    return;
}