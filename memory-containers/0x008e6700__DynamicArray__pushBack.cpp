// FUNC_NAME: DynamicArray::pushBack
void __thiscall DynamicArray::pushBack(void* this, unsigned int value) {
    int* capacityPtr = (int*)((char*)this + 0x1c);
    int* sizePtr = (int*)((char*)this + 0x18);
    int* dataPtr = (int*)((char*)this + 0x14);

    int currentCapacity = *capacityPtr;
    int currentSize = *sizePtr;

    if (currentSize == currentCapacity) {
        int newCapacity;
        if (currentCapacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = currentCapacity * 2;
        }
        // Reallocate or reserve memory for the new capacity
        FUN_008e5cf0(newCapacity);
    }

    // Calculate pointer to where the new element should be stored
    unsigned int* slot = (unsigned int*)(*dataPtr + *sizePtr * 4);
    (*sizePtr)++;
    if (slot != nullptr) {
        *slot = value;
    }
}