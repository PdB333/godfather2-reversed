// FUNC_NAME: EARSObject::deactivate
void __thiscall EARSObject::deactivate(int thisPtr) {
    // Offset +0x92: byte flag for "isActive" or "isPendingDeletion"
    if (*(char*)(thisPtr + 0x92) == '\0') {
        // If the object is not already deactivated, call the manager's removal method
        // DAT_01129a74 is a global pointer to a manager singleton (e.g., SimManager)
        // +0x2c in that class is a virtual function (e.g., SimManager::removeObject)
        (*(void (**)(void))(*DAT_01129a74 + 0x2c))();
    }
    // Mark the object as deactivated
    *(char*)(thisPtr + 0x92) = 0;

    // Offset +0x88: flag for "hasResources" or "needsCleanup"
    if (*(char*)(thisPtr + 0x88) != '\0') {
        // Release any owned resources (e.g., sound handles, stream references)
        FUN_00912030(); // Likely a cleanup function inside the object or a global manager
    }

    // Prepare a struct for delayed deletion or resource release
    // uStack_c = a 12-byte structure holding:
    //   - first word: global structure reference (DAT_01130368, possibly a deletion queue)
    //   - second word: 0 (unused or type tag)
    //   - third word: 0 (unused or associated data)
    uint uStack_c = DAT_01130368;
    uint uStack_8 = 0;
    uchar uStack_4 = 0;
    // Schedule the object for destruction via a queue mechanism
    FUN_00408a00(&uStack_c, 0); // e.g., "ObjectDeletionQueue::add"
}
```