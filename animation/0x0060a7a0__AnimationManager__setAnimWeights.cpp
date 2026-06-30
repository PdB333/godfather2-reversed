// FUNC_NAME: AnimationManager::setAnimWeights
// Function address: 0x0060a7a0
// Copies float arrays from source to internal weight buffers with change detection.
// If data changed, notifies the animation system via virtual functions.

void __thiscall AnimationManager::setAnimWeights(uint indexFlag, float* source)
{
    // indexFlag: low byte = slot index (0-255), high bit = flag selecting buffer pool
    // source: pointer to float array to copy (size given by count in EAX)
    // EAX (implicit register parameter): number of floats to copy

    int floatCount; // in_EAX (passed in EAX register)
    float* destBase;
    float* dest;
    float* src;
    int fullBlocks;
    int copiedCount;
    bool changed = false;

    uint slotIndex = indexFlag & 0xff;

    // Select destination buffer pool based on high bit
    if ((indexFlag & 0x80000000) == 0) {
        // Normal pool (e.g., blend weights for standard animation)
        destBase = (float*)&DAT_011d97f0 + slotIndex * 4;  // +0x0: base of 4-float slot
    } else {
        // Overlay/alternate pool (e.g., additive animation)
        destBase = (float*)&DAT_011ea8f0 + slotIndex * 4;
    }

    // Process in blocks of 4 floats (single slot size)
    if (floatCount > 3) {
        fullBlocks = (floatCount - 4) / 4 + 1; // number of complete 4-float blocks
        copiedCount = fullBlocks * 4;
        dest = destBase;
        src = source;

        do {
            // Compare each float in the 4-float block and copy if different
            if (dest[-1] != src[-3]) {  // first float (offset 0)
                dest[-1] = src[-3];
                changed = true;
            }
            // Access second float using pointer arithmetic
            float nextSrc = *(float*)((int)dest - (int)destBase + (int)src);
            if (dest[0] != nextSrc) {
                dest[0] = nextSrc;
                changed = true;
            }
            if (dest[1] != src[-1]) {  // third float (offset 8)
                dest[1] = src[-1];
                changed = true;
            }
            if (dest[2] != src[0]) {   // fourth float (offset 12)
                dest[2] = src[0];
                changed = true;
            }
            dest += 4;
            src += 4;
            fullBlocks--;
        } while (fullBlocks != 0);
    } else {
        copiedCount = 0;
    }

    // Process remaining floats (less than 4)
    if (copiedCount < floatCount) {
        dest = destBase + copiedCount;
        src = source + copiedCount;
        int remaining = floatCount - copiedCount;
        do {
            float value = *(float*)((int)dest - (int)destBase + (int)src);
            if (*dest != value) {
                *dest = value;
                changed = true;
            }
            dest++;
            remaining--;
        } while (remaining != 0);
    }

    if (changed) {
        if ((indexFlag & 0x80000000) != 0) {
            // Overlay pool: call notification function at vtable offset 0x178
            (**(code**)(*(int*)DAT_01205750 + 0x178))();  // e.g., AnimManager::notifyOverlayChanged
            return;
        }
        // Normal pool: call notification with slot index and block count
        int blockCount = (floatCount + 3 + ((floatCount + 3) >> 0x1f & 3)) >> 2; // ceil(floatCount/4)
        (**(code**)(*(int*)DAT_01205750 + 0x1b4))(DAT_01205750, slotIndex, destBase, blockCount);
        // e.g., AnimManager::onWeightsUpdated(slotIndex, blockCount)
    }
}