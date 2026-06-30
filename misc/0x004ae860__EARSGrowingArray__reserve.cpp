// FUNC_NAME: EARSGrowingArray::reserve

// Structure offsets:
// +0x00: data (pointer to array of elements, each 0xC bytes)
// +0x04: count (number of elements)
// +0x08: capacity (allocated element count)
// +0x0C: heap (allocator context/hint, can be null)
// +0x10: allocator (pointer to allocator object with vtable)

class EARSGrowingArray {
public:
    char* data;        // +0x00
    int count;         // +0x04
    int capacity;      // +0x08
    void* heap;        // +0x0C
    Allocator* alloc;  // +0x10 (pointer to allocator with vtable)
};

// Allocator vtable layout:
// vtable[0] = allocate(void* heap, int size) -> void*
// vtable[1] = deallocate(void* ptr, int something) -> void

typedef void* (__thiscall *AllocateFunc)(Allocator* self, void* heap, int size);
typedef void (__thiscall *DeallocateFunc)(Allocator* self, void* ptr, int something);

class Allocator {
public:
    void** vtable;  // points to function table
};

// Global default heap pointer (DAT_01218a14)
extern void* gDefaultHeap;

void __thiscall EARSGrowingArray::reserve(uint newCapacity) {
    // If new capacity is larger than current capacity
    if ((uint)this->capacity >= newCapacity) {
        return;
    }

    // Determine allocator heap – if this->heap is null, use global default
    void* heap = this->heap;
    if (heap == nullptr) {
        heap = gDefaultHeap;
    }

    // Allocate new block: element size = 12 bytes (0xC)
    int newSize = newCapacity * 12;
    char* newData = (char*)Allocate(this->alloc, heap, newSize);

    // Copy existing elements if any
    if (this->data != nullptr) {
        uint elemCount = (uint)this->count;
        for (uint i = 0; i < elemCount; i++) {
            // Copy 12 bytes per element
            *(undefined8*)(newData + i * 12) = *(undefined8*)(this->data + i * 12);
            *(undefined4*)(newData + i * 12 + 8) = *(undefined4*)(this->data + i * 12 + 8);
        }
        // Free old block
        Deallocate(this->alloc, this->data, 0);
    }

    // Update fields
    this->data = newData;
    this->capacity = newCapacity;
}

// Note: Allocate and Deallocate functions are called through vtable.
inline void* Allocate(Allocator* alloc, void* heap, int size) {
    return ((AllocateFunc)(*(void***)alloc)[0])(alloc, heap, size);
}

inline void Deallocate(Allocator* alloc, void* ptr, int zero) {
    ((DeallocateFunc)(*(void***)alloc)[1])(alloc, ptr, zero);
}