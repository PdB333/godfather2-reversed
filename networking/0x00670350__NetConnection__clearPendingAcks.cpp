// FUNC_NAME: NetConnection::clearPendingAcks
void NetConnection::clearPendingAcks() {
    // Offsets: +0x0C: mPendingAllocated (ptr)
    //          +0x14: mPendingCount (int)
    //          +0x24: mPendingEntries (array of PendingAckEntry, stride 0x14)
    // PendingAckEntry: +0x04: mEntryId (ushort)
    // The "owner" object at this+0x04 (likely NetConnection*) holds the slot table

    if (*(int*)(this + 0x0C) == 0) {
        return;
    }

    int* countPtr = (int*)(this + 0x14);
    int count = *countPtr;
    if (count <= 0) {
        *countPtr = 0;
        return;
    }

    // Iterate over entries
    PendingAckEntry* entry = (PendingAckEntry*)(this + 0x24);
    for (int i = 0; i < count; i++, entry++) {
        ushort entryId = *(ushort*)(entry + 0x04); // +4 offset

        // Access the owner's slot array (size 0x3c per slot at +0x1E, index masked to 0x7F)
        NetConnection* owner = *(NetConnection**)(this + 0x04);
        int slotIndex = entryId & 0x7F; // mask from ushort (artifact: 0x8000007F reduces to 0x7F)
        ushort* slotId = (ushort*)((uint)owner + 0x1E + slotIndex * 0x3C);

        if (*slotId == entryId) {
            // Mark slot as free
            *slotId = 0xFFFF;
            // Decrement pending count in owner (short at +0x1A)
            short* pendingCount = (short*)((uint)owner + 0x1A);
            *pendingCount = *pendingCount - 1;

            // Check if entry matches a special ID (owner's current ack ID at +0x1E1C)
            if (entryId == *(ushort*)((uint)owner + 0x1E1C)) {
                // Notify that this slot was cleared (param: owner, address of loop counter)
                // Warning: original code reused param_1 as local, here we pass &i
                FUN_00672320(owner, &i);
            }
        } else {
            // Debug error code (original: param_1 = 0x4E23) – ignore in release
        }

        // Release/cleanup helpers (likely freeing the entry itself)
        FUN_00672590();
        // Access previous entry's data? (iVar6 - 8) – can't determine, skip as artifact
        void* entryData = *(void**)((uint)entry - 8); // fallback, unreliable
        FUN_00672fd0();
        // Free two memory blocks associated with the entry
        // DAT_01206694 is a function pointer (likely operator delete or free)
        void* ptr1 = *(void**)((uint)entryData + 0x0C);
        (*DAT_01206694)(ptr1);
        (*DAT_01206694)(entryData);
    }

    // Reset count to zero
    *countPtr = 0;
}