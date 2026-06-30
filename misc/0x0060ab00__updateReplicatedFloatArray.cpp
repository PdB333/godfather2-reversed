// FUNC_NAME: updateReplicatedFloatArray

void updateReplicatedFloatArray(uint32 unused, uint32 combinedIndexFlags, float* sourceData, int32 floatCount) {
    if (combinedIndexFlags == 0)
        return;

    uint32 index = combinedIndexFlags & 0xFF;
    bool bChanged = false;

    // Select destination buffer based on high bit of combinedIndexFlags
    float* destBuffer;
    if ((combinedIndexFlags & 0x80000000) == 0) {
        // Server-side array (DAT_011d97f0)
        destBuffer = (float*)((uint8*)0x011d97f0 + index * 16);
    } else {
        // Client-side array (DAT_011ea8f0)
        destBuffer = (float*)((uint8*)0x011ea8f0 + index * 16);
    }

    int32 processed = 0;
    // Process in batches of 4 floats
    if (floatCount > 3) {
        float* src = sourceData;
        float* dst = destBuffer;
        int32 batches = (floatCount - 4U) / 4 + 1;
        processed = batches * 4;

        do {
            // Compare and copy each of the 4 floats in the block
            if (dst[0] != src[0]) {
                bChanged = true;
                dst[0] = src[0];
            }
            if (dst[1] != src[1]) {
                bChanged = true;
                dst[1] = src[1];
            }
            if (dst[2] != src[2]) {
                bChanged = true;
                dst[2] = src[2];
            }
            if (dst[3] != src[3]) {
                bChanged = true;
                dst[3] = src[3];
            }
            dst += 4;
            src += 4;
            batches--;
        } while (batches != 0);
    }

    // Process remaining floats (< 4)
    if (processed < floatCount) {
        float* dst = destBuffer + processed;
        float* src = sourceData + processed;
        int32 remaining = floatCount - processed;
        do {
            if (*dst != *src) {
                bChanged = true;
                *dst = *src;
            }
            dst++;
            src++;
            remaining--;
        } while (remaining != 0);
    }

    // If any change occurred, notify via the manager object (DAT_01205750)
    if (bChanged) {
        void* managerVtable = *(void**)0x01205750;
        if ((combinedIndexFlags & 0x80000000) != 0) {
            // Client update: call notification at vtable offset 0x178 (no args)
            typedef void (*NotifyFunc)();
            NotifyFunc notifier = *(NotifyFunc*)((uint8*)managerVtable + 0x178);
            notifier();
        } else {
            // Server update: call notification at vtable offset 0x1b4
            typedef void (*NotifyFunc)(void*, uint32, float*, int32);
            NotifyFunc notifier = *(NotifyFunc*)((uint8*)managerVtable + 0x1b4);
            int32 numGroups = (floatCount + 3 + ((floatCount + 3) >> 31 & 3)) >> 2; // ceil(floatCount/4)
            notifier(*(void**)0x01205750, index, destBuffer, numGroups);
        }
    }
}