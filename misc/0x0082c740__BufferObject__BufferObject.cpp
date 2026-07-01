//FUNC_NAME: BufferObject::BufferObject
// Address: 0x0082c740
// Constructor for a buffer object with internal allocation (size 0x40 bytes, capacity 0x10).

struct BufferObject {
    void** vtable;          // +0x00
    int field_4;            // +0x04
    void* buffer;           // +0x08 (allocated 64-byte buffer)
    int field_C;            // +0x0C
    int field_10;           // +0x10 (capacity = 16)
};

// Allocation function (likely EARS::Memory::allocate or operator new)
void* __fastcall FUN_009c8e80(size_t size);

BufferObject* __fastcall BufferObject::BufferObject(BufferObject* this) {
    this->vtable = &PTR_FUN_00d73888; // vtable pointer
    this->field_4 = 0;
    this->buffer = FUN_009c8e80(0x40); // allocate 64-byte buffer
    this->field_C = 0;
    this->field_10 = 0x10; // capacity set to 16
    return this;
}