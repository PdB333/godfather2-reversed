// FUNC_NAME: SimManager::processPendingRemovalList
void SimManager::processPendingRemovalList() {
    int errorCode;
    int index;
    ushort handleId;
    int manager;
    int *pendingCountPtr;
    int entryPtr;
    int objectPtr;

    // Save this pointer
    // this+0x0C is a non-null check for a condition (e.g., manager initialized)
    if (*(int *)(this + 0x0C) != 0) {
        pendingCountPtr = (int *)(this + 0x14);
        errorCode = 0;
        if (0 < *pendingCountPtr) {
            // +0x24: start of pending removal entry array
            entryPtr = this + 0x24;
            do {
                // Each entry size 0x14, handle ID at +4
                handleId = *(ushort *)(entryPtr + 4);
                // +0x04: pointer to the handle manager
                manager = *(int *)(this + 4);
                // Validate handle against manager's slot table (+0x1E, slot size 0x3C, up to 128 slots)
                if (*(ushort *)(manager + 0x1E + (handleId & 0x7F) * 0x3C) == handleId) {
                    // Clear the slot (set to 0xFFFF = invalid)
                    *(ushort *)(manager + 0x1E + (handleId & 0x7F) * 0x3C) = 0xFFFF;
                    // Decrement active count at +0x1A
                    *(short *)(manager + 0x1A) = *(short *)(manager + 0x1A) - 1;
                    // If handle matches special sentinel at +0x1E1C
                    if (handleId == *(ushort *)(manager + 0x1E1C)) {
                        // Call specific removal handler
                        FUN_00672320(manager, &errorCode);
                    }
                } else {
                    errorCode = 0x4E23; // Error code: handle mismatch
                }
                // Possibly enter/leave critical section
                FUN_00672590();
                // Retrieve object pointer from previous entry's +0x0C (or +0x1C for first)
                objectPtr = *(int *)(entryPtr - 8);
                FUN_00672fd0();
                // Release the object via global function pointer (likely operator delete)
                (*DAT_01206694)(*(undefined4 *)(objectPtr + 0x0C));
                (*DAT_01206694)(objectPtr);
                index++;
                entryPtr += 0x14;
            } while (index < *(int *)(this + 0x14));
        }
        // Reset pending count to 0
        *(int *)(this + 0x14) = 0;
    }
}