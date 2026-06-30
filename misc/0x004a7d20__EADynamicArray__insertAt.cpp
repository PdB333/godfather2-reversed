// FUNC_NAME: EADynamicArray::insertAt
int __fastcall EADynamicArray::insertAt(int* this, uint index)
{
    // this[0] = buffer pointer (void* data)
    // this[1] = size (number of elements)
    // this[2] = capacity (max elements)
    // Each element is 16 bytes (0x10)
    int capacity = this[2];
    if (this[1] == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        // Reallocate to new capacity
        reallocate(capacity); // FUN_004a7bf0 - likely a member function
    }

    uint oldSize = this[1];
    // If inserting at end, just clear new slot
    if (index == oldSize) {
        int* newSlot = (int*)(index * 16 + this[0]);
        if (newSlot != nullptr) {
            newSlot[0] = 0;
            *(short*)(newSlot + 1) = 0; // Note: cast to short* offset by 4 bytes
            newSlot[2] = 0;
            newSlot[3] = 0;
        }
        this[1] = oldSize + 1;
        return (int)(index * 16 + this[0]);
    }

    // Shift elements from index to end-1 forward by one slot
    int* src = (int*)(oldSize * 16 + this[0]); // last element
    int* dst = src + 4; // one slot ahead (16 bytes)
    int count = oldSize - index;
    // Actually the decompiled code shifts using pairs of 8-byte reads/writes
    // Simplified: for i = count down to 1
    int* base = (int*)this[0];
    // The loop shifts elements from index to oldSize-1 up by 16 bytes
    for (int i = count; i > 0; i--) {
        int* currentSrc = base + (oldSize - i) * 4; // each element 4 ints
        int* currentDst = currentSrc + 4;
        // Copy 8 bytes at a time (two ints) to achieve 16-byte copy
        currentDst[0] = currentSrc[0];
        currentDst[1] = currentSrc[1];
        currentDst[2] = currentSrc[2];
        currentDst[3] = currentSrc[3];
    }

    // Clear the slot at index
    int* insertSlot = (int*)(index * 16 + this[0]);
    if (insertSlot != nullptr) {
        insertSlot[0] = 0;
        *(short*)(insertSlot + 1) = 0;
        insertSlot[2] = 0;
        insertSlot[3] = 0;
    }

    this[1] = this[1] + 1; // Increase size after insertion
    return (int)(this[0] + index * 16);
}