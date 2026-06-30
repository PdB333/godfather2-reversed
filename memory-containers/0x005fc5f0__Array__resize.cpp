// FUNC_NAME: Array::resize
void __thiscall Array::resize(int* this, uint newSize)
{
    // this[0] = pointer to array buffer
    // this[1] = current size (in elements, element size 0x10)
    uint currentSize = this[1];
    if (newSize <= currentSize) {
        if (newSize < currentSize) {
            this[1] = newSize; // shrink, no reallocation
        }
        return;
    }

    // Grow: reallocate buffer to hold newSize elements
    FUN_005fc8f0(newSize); // likely realloc or allocate new buffer, updates this[0]?

    uint defaultFirstField = DAT_00e2e50c; // global default for first field of each element
    uint i = currentSize;
    if ((newSize - i) > 3) {
        int baseOffset = i * 0x10;
        int bulkCount = ((newSize - i) - 4) / 4 + 1;
        i = i + bulkCount * 4;
        // Bulk initialize 4 elements at a time (0x40 bytes)
        do {
            // Initialize element at baseOffset
            uint* elem = (uint*)(this[0] + baseOffset);
            if (elem) {
                elem[0] = defaultFirstField;
                elem[1] = 0;
                elem[2] = 0;
                elem[3] = 0;
            }
            // Next element at +0x10
            elem = (uint*)(baseOffset + 0x10 + this[0]);
            if (elem) {
                elem[0] = defaultFirstField;
                elem[1] = 0;
                elem[2] = 0;
                elem[3] = 0;
            }
            // Next at +0x20
            elem = (uint*)(baseOffset + 0x20 + this[0]);
            if (elem) {
                elem[0] = defaultFirstField;
                elem[1] = 0;
                elem[2] = 0;
                elem[3] = 0;
            }
            // Next at +0x30
            elem = (uint*)(this[0] + baseOffset + 0x30);
            if (elem) {
                elem[0] = defaultFirstField;
                elem[1] = 0;
                elem[2] = 0;
                elem[3] = 0;
            }
            baseOffset += 0x40;
            bulkCount--;
        } while (bulkCount != 0);
    }

    // Initialize remaining elements one by one
    while (i < newSize) {
        uint* elem = (uint*)(this[0] + i * 0x10);
        if (elem) {
            elem[0] = defaultFirstField;
            elem[1] = 0;
            elem[2] = 0;
            elem[3] = 0;
        }
        i++;
    }

    this[1] = newSize;
}