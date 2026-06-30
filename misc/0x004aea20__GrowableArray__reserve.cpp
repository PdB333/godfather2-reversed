// FUNC_NAME: GrowableArray::reserve

// Array element size: 0x14 (20) bytes
struct GrowableArray {
    void* data;               // +0x00
    unsigned int size;        // +0x04
    unsigned int capacity;    // +0x08
    void* allocator;          // +0x0C
    struct AllocatorVTable* allocVTable; // +0x10
};

struct AllocatorVTable {
    void* (__cdecl* allocate)(unsigned int size, void* allocator);   // +0x00
    void   (__cdecl* deallocate)(void* ptr, unsigned int unknown);   // +0x04
};

void __thiscall GrowableArray::reserve(unsigned int newCapacity) {
    if (newCapacity > this->capacity) {
        // Use custom allocator or default
        void* alloc = this->allocator;
        if (alloc == NULL) {
            alloc = &DAT_01218a14; // default allocator
        }

        // Allocate new memory block (each element is 0x14 bytes)
        void* newData = this->allocVTable->allocate(newCapacity * 0x14, alloc);

        // Copy existing elements to new block
        if (this->data != NULL) {
            unsigned int count = 0;
            if (this->size != 0) {
                for (unsigned int i = 0; i < this->size; i++) {
                    memcpy((char*)newData + i * 0x14, (char*)this->data + i * 0x14, 0x14);
                }
            }

            // Free old memory
            this->allocVTable->deallocate(this->data, 0);
        }

        this->data = newData;
        this->capacity = newCapacity;
    }
}