// FUNC_NAME: EARSByteArray::insertElements
void __thiscall EARSByteArray::insertElements(int this, void* insertionPos, int numElements) {
    int currentEnd = *(int*)(this + 0x08);            // pointer to one past last element
    int capacityEnd = *(int*)(this + 0x18);           // end of allocated memory
    int bufferStart = *(int*)(this + 0x1c);           // base of allocated buffer
    int capacityCount = *(int*)(this + 0x20);         // number of elements allocated

    int elementsAfterPos = (currentEnd - (int)insertionPos) >> 3;  // number of elements from insertion point to current end

    if (elementsAfterPos < numElements) {
        // Not enough elements after insertion point; pad with zeros at the end
        int padCount = numElements - elementsAfterPos;

        // Check if buffer has room for the padding
        if (capacityEnd - currentEnd <= padCount * 8) {
            // Need to grow the buffer first
            growBuffer(this);  // FUN_00635c70
        }

        elementsAfterPos += padCount;

        // Write zero-initialized elements at the end
        do {
            *(undefined4*)currentEnd = 0;
            *(undefined4*)(currentEnd + 4) = 0;
            currentEnd += 8;
            padCount--;
        } while (padCount != 0);
    }

    elementsAfterPos -= numElements;  // actual number of elements to shift

    // Allocate a default element value (or reuse from pool)
    int defaultElement = allocateDefault(elementsAfterPos, 1);  // FUN_00637c50

    if (elementsAfterPos > 0) {
        // Shift existing elements forward by numElements positions
        int offset = elementsAfterPos * -8;  // negative offset from current end
        int shiftCount = elementsAfterPos;

        do {
            // Get pointer to element at the old position
            undefined4* src = (undefined4*)(currentEnd + offset);
            // Get a reusable element slot (or allocate a new one if sentinel)
            undefined4* dst = (undefined4*)getReusableElement();  // FUN_00637f10
            if (dst == &g_sentinel) {  // checker
                dst = (undefined4*)getDefault();  // FUN_00637d60
            }
            // Copy the 8-byte element
            *dst = *src;
            dst[1] = src[1];

            offset += 8;
            shiftCount--;
        } while (shiftCount != 0);
    }

    // Commit the insertion (possibly adjusting internal state)
    commitInsert();  // FUN_00638920

    // Write a "packet" with type 3 and a count (maybe for replay/logging)
    undefined4* packet = (undefined4*)writePacket();  // FUN_00638020
    *packet = 3;
    packet[1] = (float)elementsAfterPos;

    // Move current end backward to make room for the inserted elements
    currentEnd -= numElements * 8;
    *(int*)(this + 0x08) = currentEnd;

    // Write the inserted elements (type 5 packet with the default value)
    packet = (undefined4*)currentEnd;
    *packet = 5;
    packet[1] = defaultElement;

    // Check if remaining free space is too small; if so, reallocate the buffer
    if (capacityEnd - currentEnd < 9) {
        // Grow buffer
        int oldSize = capacityCount * 8;
        int newCount = capacityCount * 2;
        if (capacityCount < 1) {
            newCount = capacityCount + 0x15;
        }
        int newBuffer = reallocateBuffer(oldSize, newCount * 8);  // FUN_006279a0
        *(int*)(this + 0x1c) = newBuffer;            // new buffer start
        *(int*)(this + 0x20) = newCount;              // new capacity count
        *(int*)(this + 0x18) = newBuffer - 0xa8 + newCount * 8;  // new capacity end
        rebalancePointers();  // FUN_00635b50
    }

    // Advance current end past the inserted elements
    *(int*)(this + 0x08) = currentEnd + 8;
}