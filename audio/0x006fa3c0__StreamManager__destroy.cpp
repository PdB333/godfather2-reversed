// FUNC_NAME: StreamManager::destroy
void __fastcall StreamManager::destroy(StreamManager *this)
{
    int *pStreamList; // piVar1, offset +0x3C
    bool bPending; // cVar3
    int slotIndex; // iStack_4, loop from 29 down to 0
    StreamSlot *pSlot; // pointer to current slot (end)
    StreamSlot *pSlotStart; // puVar5, start of current slot

    // Set vtables for top-level object
    this->vtable = (int)&PTR_FUN_00d60a1c; // +0x00
    this->anotherVtable = (int)&PTR_LAB_00d60a18; // +0x0C (offset 3)

    // Clear pending flag at offset +0x38 (word 14)
    this->pendingClear = 0; // +0x38 (param_1[0xe])

    // Free an internal list if present
    pStreamList = (int *)((int)this + 0x3C); // +0x3C (param_1[0xf])
    if (*pStreamList != 0) {
        sub_4daf90(pStreamList); // free
        *pStreamList = 0;
    }

    // Wait for pending operations to complete
    bPending = true;
    while (((this->someCounter1 != 0) || (this->someCounter2 != 0)) && (bPending)) {
        bPending = sub_6fa0f0();  // process pending work
    }

    // Clear counters and free associated buffers
    this->someCounter2 = 0;   // +0x14 (param_1[5])
    sub_9c8f10(this->pBuffer1); // +0x10 (param_1[4])
    this->pBuffer1 = 0;
    this->someFlag = 0;       // +0x18 (param_1[6])
    this->someCounter1 = 0;   // +0x20 (param_1[8])
    sub_9c8f10(this->pBuffer2); // +0x1C (param_1[7])
    this->pBuffer2 = 0;
    this->anotherFlag = 0;    // +0x24 (param_1[9])

    // Decrement global reference (likely static)
    sub_6f9c90();

    // Clear a slot counter
    this->slotCounter = 0;    // +0x34 (param_1[0xd])

    // Another static call
    sub_6f9c20();

    // Destroy all 30 slots (indices 29 down to 0)
    for (slotIndex = 29; slotIndex >= 0; --slotIndex) {
        // Calculate the end of the current slot: offset 0x1b5 (0x6D4) minus 0x38 per slot
        int offsetEnd = 0x1b5 + 0xe * slotIndex; // Actually initial puVar4 = this + 0x1b5, then iterate backwards
        // Simplified: we process slots at decreasing addresses.
        // The first slot is at this + 0x1a7, each 0x38 bytes.
        pSlot = (StreamSlot *)((int)this + 0x1a7 + slotIndex * 0x38);
        pSlotStart = pSlot;

        // Set vtable for each slot
        pSlotStart->vtable = (int)&PTR_FUN_00d60a08;

        // If slot has a data pointer, copy from it (size 0x1ff bytes)
        if (pSlot->dataPtr != 0) {
            sub_4035f0(pSlot->dataPtr, 0x1ff, pSlotStart);
        }

        // Free each sub-element in an array (each sub-element 8 bytes)
        int subCount = pSlot->subCount;
        while (subCount-- > 0) {
            if (*(int *)(pSlot->subArray + subCount * 8) != 0) {
                sub_4daf90((int *)(pSlot->subArray + subCount * 8));
            }
        }

        // Free the sub-array itself
        if (pSlot->subArray != 0) {
            sub_9c8f10(pSlot->subArray);
        }

        // Call slot destructor function if pointer exists
        if (pSlot->destructorArg != 0) {
            ((void (*)(void*))pSlot->destructorFunc)((void*)pSlot->destructorArg);
        }

        // Memory check / debug call
        sub_4083d0();
    }

    // Final free of the list pointer (should be zero already)
    if (this->pStreamList != 0) {
        sub_4daf90((int *)&this->pStreamList);
    }

    // Free additional buffers (should be zero)
    if (this->pBuffer3 != 0) {
        sub_9c8f10(this->pBuffer3);
    }
    if (this->pBuffer2 != 0) {
        sub_9c8f10(this->pBuffer2);
    }
    if (this->pBuffer1 != 0) {
        sub_9c8f10(this->pBuffer1);
    }

    // Update vtable to disabled state
    this->anotherVtable = (int)&PTR_LAB_00d60a04;

    // Clear global instance count
    g_streamManagerInstanceCount = 0;

    // Final memory check
    sub_4083d0();
}

// Helper struct for slot
struct StreamSlot {
    int vtable;          // +0x00
    char pad_4[8];       // +0x04 to +0x0B
    void *dataPtr;       // +0x0C (puVar4[-0xb])
    void *destructorArg; // +0x10 (puVar4[-10])
    char pad_14[8];      // +0x14 to +0x1B
    void (*destructorFunc)(void*); // +0x1C (puVar4[-7])
    void *subArray;      // +0x20 (puVar4[-6])
    int subCount;        // +0x24 (puVar4[-5])
    // remaining 0x14 bytes (0x38 total)
};

// Note: field offsets are approximate due to inverted access pattern.
// The actual struct layout may differ; this is a reconstruction based on decompiled code.