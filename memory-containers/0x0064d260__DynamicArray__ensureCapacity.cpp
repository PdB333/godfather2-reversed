// FUNC_NAME: DynamicArray::ensureCapacity
void __thiscall DynamicArray::ensureCapacity(unsigned int needed) {
    // +0x00: size (number of used elements)
    // +0x04: capacity (allocated element count)
    // +0x08: data pointer (array of 4-byte elements)
    if (needed <= this->capacity) {
        return;
    }

    // Compute new capacity: round up to next multiple of 16 elements,
    // but if already a multiple, add 16 more (to reduce reallocation frequency).
    unsigned int newCapacity = needed + (0x10 - (needed & 0xF));

    int* newData = (int*)malloc(newCapacity * sizeof(int));

    // Copy existing elements from old data to new buffer.
    // The helper (at 0x0064d2d0) copies this->size elements from old data to new data.
    memcpy(newData, this->data, this->size * sizeof(int));

    free(this->data);
    this->data = newData;
    this->capacity = newCapacity;
}