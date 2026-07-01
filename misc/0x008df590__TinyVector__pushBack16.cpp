// FUNC_NAME: TinyVector::pushBack16
void __thiscall TinyVector::pushBack16(int *this, const undefined4 *element) {
    int currentSize;
    int capacity;
    int *newBuffer;

    currentSize = this[1]; // +0x04: current number of elements
    capacity = this[2];    // +0x08: allocated capacity

    if (currentSize == capacity) {
        // Double capacity if non-zero, or set to 1 if empty
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity = capacity * 2;
        }
        // Resize the internal buffer (allocates new memory, copies old elements)
        FUN_008defe0(capacity); // (capacity) -> likely reallocates and updates this[0]
    }

    // Compute pointer to the new slot
    int *slot = (int *)(this[0] + currentSize * 0x10); // +0x00: pointer to buffer
    // Increment size
    this[1] = currentSize + 1;

    if (slot != (int *)0x0) {
        // Copy 16 bytes (4 dwords) from the incoming element
        slot[0] = element[0];
        slot[1] = element[1];
        slot[2] = element[2];
        slot[3] = element[3];
    }
}