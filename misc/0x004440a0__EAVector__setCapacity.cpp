// FUNC_NAME: EAVector::setCapacity

// Reconstructed custom dynamic array (similar to std::vector) from EA EARS engine.
// This function increases capacity to at least newCapacity elements.
// Structure (uint32 offsets from this pointer in ESI):
//   +0x00: data pointer (element array)
//   +0x04: size (number of elements currently in use)
//   +0x08: capacity (maximum elements before reallocation)
//   +0x0C: pointer to allocator object
//   +0x10: pointer to allocator vtable (two function pointers: allocate, deallocate)

struct EAVectorAllocatorVTable {
    void* (*allocate)(size_t size, void* allocator); // offset 0
    void  (*deallocate)(void* ptr, size_t size);     // offset 4
};

struct EAVector {
    int*       data;         // +0x00
    int        size;         // +0x04
    int        capacity;     // +0x08
    void*      allocator;    // +0x0C (default = &DAT_01218a14)
    EAVectorAllocatorVTable* vtable; // +0x10
};

void __thiscall EAVector::setCapacity(EAVector* this, uint newCapacity) {
    int* oldData;
    int* newData;
    uint i;
    EAVectorAllocatorVTable* vt;

    if (this->capacity < newCapacity) {
        // Use the allocator's allocate function: vtable->allocate(size, allocator)
        vt = this->vtable;
        newData = (int*)vt->allocate(newCapacity * sizeof(int), this->allocator);
        if (this->data != 0) {
            i = 0;
            if (this->size != 0) {
                do {
                    // Copy each element (8 bytes each: two ints)
                    newData[i * 2]     = this->data[i * 2];
                    newData[i * 2 + 1] = this->data[i * 2 + 1];
                    i++;
                } while (i < (uint)this->size);
            }
            // Deallocate old memory
            vt->deallocate(this->data, 0);
        }
        this->data     = newData;
        this->capacity = newCapacity;
    }
}