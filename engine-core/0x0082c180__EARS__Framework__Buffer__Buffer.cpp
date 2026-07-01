// FUNC_NAME: EARS::Framework::Buffer::Buffer
// Address: 0x0082c180
// Role: Constructor for a dynamically allocated buffer with initial capacity of 16 elements (4 bytes each). Allocates a 64-byte buffer.

// Class definition (partial)
class EARS::Framework::Buffer {
public:
    // VTable pointer (offset 0x00)
    void** vtable;
    // Unknown field (offset 0x04) - possibly flags or reference count
    int unknown;
    // Pointer to allocated data buffer (offset 0x08)
    void* data;
    // Current number of elements (offset 0x0C)
    int size;
    // Capacity in elements (offset 0x10)
    int capacity;

    // Constructor
    __fastcall Buffer(void* thisPtr);
};

// External allocation function (likely operator new or custom allocator)
extern void* __cdecl allocateMemory(size_t size);

__fastcall Buffer::Buffer(void* thisPtr) {
    Buffer* self = (Buffer*)thisPtr;

    // Set vtable pointer (from global data section)
    self->vtable = (void**)&PTR_FUN_00d7378c; // +0x00

    // Initialize unknown field to 0
    self->unknown = 0; // +0x04

    // Allocate a buffer of 64 bytes (0x40) for 16 elements of 4 bytes each
    self->data = allocateMemory(0x40); // +0x08

    // Initialize size to 0
    self->size = 0; // +0x0C

    // Set capacity to 16 elements
    self->capacity = 0x10; // +0x10
}