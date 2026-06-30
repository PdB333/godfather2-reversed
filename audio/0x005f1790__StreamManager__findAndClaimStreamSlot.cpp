// FUNC_NAME: StreamManager::findAndClaimStreamSlot
uint __cdecl StreamManager::findAndClaimStreamSlot(StreamDescriptor* streamDesc, float timeValue) {
    int currentIter;
    uint result;
    int slotCount;
    bool listExists;
    bool flagCheck;

    currentIter = g_streamListHead; // DAT_011a0ef0
    slotCount = 0;
    listExists = g_streamListHead != 0;

    streamDesc->slotIndex = 1; // offset +0x06: byte, mark as first slot

    if (!listExists) {
        return result & 0xffffff00; // unchanged if no list exists
    }

    do {
        // Check if current node has a valid stream data pointer at +0x2c
        if (*(void**)(currentIter + 0x2c) != nullptr) {
            int streamId = **(int**)(currentIter + 0x2c); // dereferenced to get ID at offset 0
            if (streamId == streamDesc->id) { // streamDesc->id is at *param_1 (offset 0)
                slotCount++;
                streamDesc->slotIndex = (byte)slotCount; // store current count
                int id = streamDesc->id;
                if (streamDesc->maxSlots <= slotCount) { // offset +0x05: byte
                    // Check override flag
                    if ((streamDesc->flags & 0x10) == 0) { // offset +0x28
                        if (*(float*)(currentIter + 0x50) <= timeValue) {
                            goto RELEASE_STREAM;
                        }
                    } else {
                        if (*(float*)(currentIter + 0x50) + g_streamTimeoutTolerance < timeValue) {
RELEASE_STREAM:
                            result = FUN_005f1ef0(currentIter);
                            return result & 0xffffff00;
                        }
                    }
                    // Return success with low byte set to 1, high bits from id>>8
                    return (uint)((id >> 8) & 0xFFFFFF) | 1; // CONCAT31((int3)(id>>8),1)
                }
            }
        }
        currentIter = *(int*)(currentIter + 4); // linked list next
        if (currentIter == 0) {
            return result & 0xffffff00;
        }
    } while (true);
}