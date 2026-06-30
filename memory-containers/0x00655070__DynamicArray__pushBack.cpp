// FUNC_NAME: DynamicArray::pushBack

void DynamicArray::pushBack(Item* item) {
    // Perform some initialization or validation
    sub_6551b0();

    // Get some status or allocation result
    int status = sub_655250();
    if (status != 0) {
        sub_6576b0(this, status);
    }

    // Increment item's reference count (offset +0x8)
    item->refCount++;

    // Pointer to the count of elements stored at offset +0x24
    int* sizePtr = (int*)((uintptr_t)this + 0x24);
    // Pointer to the array base pointer stored at offset +0x2c
    int* arrayBase = *(int**)((uintptr_t)this + 0x2c);

    // Ensure capacity for the new element
    sub_657bf0(*sizePtr + 1);

    // Increase the element count
    (*sizePtr)++;

    // If the array is allocated, store the item at the new last index
    if (arrayBase != nullptr) {
        arrayBase[*sizePtr - 1] = (int)item;
    }
}