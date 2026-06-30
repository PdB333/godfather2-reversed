// FUNC_NAME: DynamicArray::reserve
int DynamicArray::reserve(int newCount) {
    // +0x00: unknown (maybe count or vtable)
    // +0x04: capacity (int)
    // +0x0C: array pointer (void*)
    if (this->capacity < newCount) {
        int remainder = newCount & 0x8000003f; // low 6 bits + sign bit
        if ((int)remainder < 0) {
            remainder = (remainder - 1 | 0xffffffc0) + 1; // sign extend for negative
        }
        int alignedCount = newCount + (0x80 - remainder); // round to next multiple of 64 and add 64

        void* newBuffer = _realloc(this->array, alignedCount * 4);
        if (newBuffer == nullptr) {
            return 0xfffffffe; // -2
        }
        this->array = newBuffer;
        int oldCapacity = this->capacity;
        this->capacity = alignedCount;
        // Zero-fill the new elements (each 4 bytes)
        for (int i = oldCapacity; i < this->capacity; i++) {
            *(int*)((char*)this->array + i * 4) = 0;
        }
    }
    return 0;
}