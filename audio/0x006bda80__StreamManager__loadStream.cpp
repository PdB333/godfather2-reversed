// FUNC_NAME: StreamManager::loadStream

void __thiscall StreamManager::loadStream(int this, int streamOwner) {
    undefined4 handle;
    undefined **local_18; // linked list head pointer
    int local_14; // node pointer
    undefined4 local_10; // previous node pointer
    undefined4 local_c; // context pointer
    undefined ***local_8; // anchor pointer
    undefined1 local_4; // sentinel

    // If a handle already exists, close it
    if (*(int *)(this + 0xd0) != 0) {
        FUN_00791350(this + 0x50); // ReleaseStreamLock? (call to lock/unlock)
        *(undefined4 *)(this + 0xd0) = 0;
    }

    // Create a new handle (maybe open a file or allocate a resource)
    handle = FUN_007351c0(); // CreateStreamHandle? (returns a handle)
    *(undefined4 *)(this + 0xd0) = handle;

    FUN_00791e70(this + 0x50); // AcquireStreamLock? (counterpart)

    // Set flag indicating stream is active
    *(uint *)(this + 0x54) |= 0x10000;

    // If there is a stream owner (parent object), register this stream in its list
    if (*(int *)(this + 0x80) != 0) {
        local_18 = &PTR_FUN_00e31e2c; // global function pointer table? (maybe for cleanup)
        if (streamOwner == 0) {
            local_14 = 0;
        }
        else {
            local_14 = streamOwner + 0x48; // +0x48 = pointer to linked list node
        }

        local_10 = 0;
        if (local_14 != 0) {
            local_10 = *(undefined4 *)(local_14 + 4); // Prev pointer? (linked list)
            *(int **)(local_14 + 4) = &local_14; // Set next pointer? (old code: stores address of local_14)
        }

        local_c = *(undefined4 *)(this + 0x80); // Get owner list head
        local_8 = &local_18; // Points to the head of the global list? (maybe for unregister)
        local_4 = 0;
        FUN_00408a00(&local_c, 0); // Insert node into list? (or register)

        if (local_14 != 0) {
            FUN_004daf90(&local_14); // Cleanup temporary node (maybe release reference)
        }
    }

    return;
}