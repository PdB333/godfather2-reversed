// FUNC_NAME: EAVector::resize(uint)
void __thiscall EAVector::resize(int *this, uint newSize)
{
    undefined4 defaultVal;
    int currentSize;
    int *dataPtr;
    uint i;
    uint count;

    // If newSize <= current size, optionally shrink (just update size, no deallocation)
    if (newSize <= (uint)this[1]) {
        if (newSize < (uint)this[1]) {
            this[1] = newSize;
        }
        return;
    }

    // Reallocate underlying buffer to accommodate newSize (called only when growing)
    FUN_005fc8f0(newSize);

    // Default value for new elements (constant from .data)
    defaultVal = DAT_00e2e50c;

    // Optimization: bulk-initialize 4 elements at a time (64 bytes)
    count = this[1]; // old size
    if (3 < (int)(newSize - count)) {
        int offset = count * 0x10; // element size 16 bytes
        int batchCount = ((newSize - count) - 4 >> 2) + 1; // number of 4-element batches
        count += batchCount * 4;

        do {
            // Initialize 4 consecutive elements
            dataPtr = (int *)(this[0] + offset);
            if (dataPtr) {
                *dataPtr = defaultVal;
                dataPtr[1] = 0;
                dataPtr[2] = 0;
                dataPtr[3] = 0;
            }

            dataPtr = (int *)(this[0] + offset + 0x10);
            if (dataPtr) {
                *dataPtr = defaultVal;
                dataPtr[1] = 0;
                dataPtr[2] = 0;
                dataPtr[3] = 0;
            }

            dataPtr = (int *)(this[0] + offset + 0x20);
            if (dataPtr) {
                *dataPtr = defaultVal;
                dataPtr[1] = 0;
                dataPtr[2] = 0;
                dataPtr[3] = 0;
            }

            dataPtr = (int *)(this[0] + offset + 0x30);
            if (dataPtr) {
                *dataPtr = defaultVal;
                dataPtr[1] = 0;
                dataPtr[2] = 0;
                dataPtr[3] = 0;
            }

            offset += 0x40;
            batchCount--;
        } while (batchCount != 0);
    }

    // Initialize remaining elements
    if (count < newSize) {
        int offset = count * 0x10;
        int remaining = newSize - count;
        do {
            dataPtr = (int *)(this[0] + offset);
            if (dataPtr) {
                *dataPtr = defaultVal;
                dataPtr[1] = 0;
                dataPtr[2] = 0;
                dataPtr[3] = 0;
            }
            offset += 0x10;
            remaining--;
        } while (remaining != 0);
    }

    // Update element count
    this[1] = newSize;
}