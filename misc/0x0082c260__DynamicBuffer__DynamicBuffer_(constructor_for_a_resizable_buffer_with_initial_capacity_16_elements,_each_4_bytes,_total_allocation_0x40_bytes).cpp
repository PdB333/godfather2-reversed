// FUNC_NAME: DynamicBuffer::DynamicBuffer (constructor for a resizable buffer with initial capacity 16 elements, each 4 bytes, total allocation 0x40 bytes)

class DynamicBuffer {
public:
    void** vtable;     // +0x0
    int field_0x4;      // +0x4 (unknown, zeroed)
    void* data;         // +0x8 (allocated buffer, 64 bytes)
    int field_0xC;      // +0xC (zeroed)
    int capacity;       // +0x10 (initial capacity = 16 elements)

    // __thiscall constructor
    DynamicBuffer() {
        vtable = (void**)&PTR_FUN_00d737b0;   // set vtable for DynamicBuffer
        field_0x4 = 0;
        data = allocMem(0x40);                // allocate 64 bytes (16 * 4)
        field_0xC = 0;
        capacity = 0x10;                      // capacity = 16 elements
    }
};