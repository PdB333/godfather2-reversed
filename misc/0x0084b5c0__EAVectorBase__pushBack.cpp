// FUNC_NAME: EAVectorBase::pushBack
void __thiscall EAVectorBase::pushBack(int* value) {
    // struct layout:
    // +0x00: int* data    // pointer to dynamic array of ints
    // +0x04: int size     // current number of elements
    // +0x08: int capacity // allocated capacity

    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : (capacity * 2);
        growCapacity(newCapacity);
    }

    int* slot = data + size;
    size++;
    if (slot != nullptr) {
        *slot = *value;
    }
}