// FUNC_NAME: Vector::grow (internal resize method for a dynamic array with allocator vtable)
// Function at 0x006e9220 - grows the capacity of a vector-like container if needed.

// Class layout (offsets):
// +0x00: mData (int*)
// +0x04: mSize (uint)
// +0x08: mCapacity (uint)
// +0x0C: mAllocatorHint (void*) - alternate allocator instance, if null uses default
// +0x10: mAllocator (Allocator*) - pointer to an allocator object with virtual functions
//   The allocator vtable (at *mAllocator) has at least:
//   +0x00: allocate(size_t bytes, void* hint) -> void*
//   +0x04: deallocate(void* ptr, size_t bytes) -> void

struct Allocator {
    virtual void* allocate(uint bytes, void* hint);
    virtual void  deallocate(void* ptr, uint bytes);
};

struct Vector {
    int*       mData;           // +0x00
    uint       mSize;           // +0x04
    uint       mCapacity;       // +0x08
    void*      mAllocatorHint;  // +0x0C
    Allocator* mAllocator;      // +0x10
};

// Global default allocator (referenced as DAT_01218a14)
extern Allocator gDefaultAllocator;

void __thiscall Vector::grow(Vector* this, uint newCapacity) {
    if (this->mCapacity >= newCapacity) {
        return;
    }

    // Determine which allocator hint to use
    void* hint = this->mAllocatorHint;
    if (hint == nullptr) {
        hint = &gDefaultAllocator;
    }

    Allocator* alloc = this->mAllocator; // allocator object with vtable

    // Allocate new buffer (size = newCapacity * 4 bytes)
    int* newData = static_cast<int*>(alloc->allocate(newCapacity * 4, hint));

    // Copy existing elements from old buffer to new buffer
    if (this->mData != nullptr) {
        uint idx = 0;
        int* dest = newData;
        int* src = this->mData;
        uint count = this->mSize;
        while (idx < count) {
            if (dest != nullptr) { // Safety check, should always be true
                *dest = *src;
            }
            idx++;
            dest++;
            src++;
        }
        // Free the old buffer
        alloc->deallocate(this->mData, 0);
    }

    // Update the vector's data pointer and capacity
    this->mData = newData;
    this->mCapacity = newCapacity;
}