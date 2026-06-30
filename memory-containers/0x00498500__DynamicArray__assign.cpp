// FUNC_NAME: DynamicArray::assign
// This function performs a deep copy from another DynamicArray instance.
// It allocates a new buffer if the source has non-zero capacity and copies
// up to 'count' elements (each 4 bytes). The structure layout is:
// +0x00: data pointer (int*)
// +0x04: count (number of used elements)
// +0x08: capacity (allocated element count)

#include <cstdint>

// forward declaration of memory allocation helper (likely operator new or custom alloc)
int* __cdecl allocateArray(int size); // at 0x009c8e80

struct DynamicArray {
    int* data;     // +0x00
    int count;     // +0x04
    int capacity;  // +0x08

    // copy assign: deep copy from 'other' into this
    DynamicArray* assign(DynamicArray* other);
};

// __thiscall: ecx = this, stack = other
DynamicArray* DynamicArray::assign(DynamicArray* other) {
    int newCapacity = other->capacity;
    this->capacity = newCapacity;
    this->count = other->count;

    if (newCapacity == 0) {
        this->data = nullptr;
    } else {
        // allocate memory for the new array (each element is 4 bytes)
        int* newData = allocateArray(newCapacity * 4);
        this->data = newData;

        // copy all used elements
        for (uint32_t i = 0; i < (uint32_t)this->count; i++) {
            newData[i] = other->data[i];
        }
    }
    return this;
}