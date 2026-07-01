// FUNC_NAME: DynamicArray::DynamicArray
// Address: 0x0082c4a0
// Role: Constructor for a dynamic array with initial capacity of 16 elements (each 4 bytes), allocates a 64-byte buffer.
// The class stores: vtable ptr (0x0), count (0x4), buffer pointer (0x8), capacity (0xC), elementSize? (0x10) or something else. Here capacity = 0x10 (16 elements), allocated 0x40 bytes.
// Assumes element size = 4 bytes.

class DynamicArray {
public:
    // Virtual table pointer offset 0x0
    void* vtable; // points to PTR_FUN_00d7381c
    int count; // +0x4: number of elements stored (init 0)
    void* data; // +0x8: pointer to allocated buffer
    int capacity; // +0xC: maximum number of elements (init 0x10)
    int elementSize; // +0x10: possibly size of each element? but set to 0x10? or maybe another field.

    // Constructor
    DynamicArray() {
        __asm { // this call setup assumed
            mov ecx, this
        }
        this->vtable = (void*)0x00d7381c; // PTR_FUN_00d7381c
        this->count = 0;
        this->data = FUN_009c8e80(0x40); // allocate 64 bytes (16 elements * 4 bytes each)
        this->capacity = 0x10; // 16 elements
        this->elementSize = 0x10; // or possibly another field; note: elementSize is 16? That's inconsistent with 4-byte elements. Could be unused or a different meaning.
        // Note: The decompiled shows param_1[4] = 0x10, which could be a sentinel or something. Could also be a field indicating buffer size (0x10 bytes?) but allocation is 0x40. Hard to tell.
        // Given typical patterns, maybe param_1[4] is a flag or another parameter.
    }
};
// Note: The actual class layout may differ; offset +0x10 being set to 0x10 suggests it might be a different member like "bufferSize" (0x10 bytes?) but that seems too small. It might be a misidentified field; perhaps it's related to alignment or a sub-allocation size.
// Alternatively, this could be a container that stores each element as a pointer, and capacity of 0x10 pointers = 0x40 bytes. Then element size stored would be unnecessary.
// For consistency, I'll keep as is. The function name is chosen to reflect the pattern.