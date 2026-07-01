// FUNC_NAME: EARS::Framework::AudioResourcePool::acquireHandle
undefined4 __thiscall EARS::Framework::AudioResourcePool::acquireHandle(
    int this,
    undefined4 param_2,
    undefined4 param_3,
    undefined4 param_4,
    undefined4 resourceNameId,
    int priorityType,
    int loopMode,
    int channelMode,
    int playbackMode,
    undefined4 extraParam1,
    undefined4 extraParam2,
    undefined4 extraParam3,
    undefined4 extraParam4)
{
    undefined4* freeListHead;
    undefined4 resultHandle;
    undefined4* allocaSlotPtr;
    uint flags;

    // Lookup resource ID by name (or hash)
    resultHandle = lookupResourceId(resourceNameId);

    flags = 0;
    if (loopMode == 1) {
        flags = 8;
    }
    if (channelMode == 1) {
        flags |= 0x20;
    }
    else if (channelMode == 2) {
        flags |= 0x10;
    }
    if (playbackMode == 0) {
        flags |= 0x200;
    }
    else if (playbackMode == 1) {
        flags |= 0x100;
    }
    if (priorityType == 1) {
        flags |= 1;
    }
    else if (priorityType == 3) {
        flags |= 4;
    }

    // Global check: if audio system not fully initialized, force background flag
    if (*(char*)(DAT_0112af90 + 0x48) == '\0') {
        flags |= 0x80;
        acquireGlobalMutex(&DAT_011301a8);
    }

    // Prepare the stack variable for the allocation result
    allocaSlotPtr = (undefined4*)FUN_0094ab00(&resourceNameId);

    // Check if pool has free slots or is in valid state
    if ((*(int*)(this + 0x5c) == 0) &&
        ((*(int*)(this + 0x58) == 0 || ((*(byte*)(this + 0x4c) & 1) == 0)))) {
        // Pool not ready, attempt initialization
        initializeAudioPool();
    }

    // Try to get a free slot from the pool's free list (+0x5c)
    freeListHead = *(undefined4**)(this + 0x5c);
    if (freeListHead != (undefined4*)0x0) {
        // Remove head from free list
        undefined4 nextFree = *freeListHead;
        *(int*)(this + 0x38) = *(int*)(this + 0x38) + 1;  // increment allocated count
        *(int*)(this + 0x34) = *(int*)(this + 0x34) - 1;  // decrement free count
        *(undefined4*)(this + 0x5c) = nextFree;

        // If free slot was valid, create the resource instance
        if (freeListHead != (undefined4*)0x0) {
            undefined4 createdHandle = createAudioResource(resultHandle, param_2, param_3, param_4,
                                                          flags, extraParam1, extraParam2,
                                                          extraParam3, extraParam4);
            *allocaSlotPtr = createdHandle;
            return resultHandle;
        }
    }

    // No free slot available, return null handle
    *allocaSlotPtr = 0;
    return resultHandle;
}