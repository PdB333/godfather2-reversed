// FUNC_NAME: MemoryBuffer::constructor
class MemoryBuffer {
public:
    // vtable pointer at +0x00
    void** vtable;          // set to &PTR_FUN_00d73864
    int field_4;            // set to 0
    void* buffer;           // allocated with FUN_009c8e80(0x40) // +0x08
    int field_C;            // set to 0 // +0x0C
    int capacity;           // set to 0x10 (16) // +0x10

    // Constructor: initializes a 64-byte buffer and sets capacity to 16
    MemoryBuffer* __thiscall constructor(MemoryBuffer* this) {
        this->vtable = &PTR_FUN_00d73864;    // vtable for MemoryBuffer
        this->field_4 = 0;
        this->buffer = FUN_009c8e80(0x40);    // allocate 64 bytes (likely operator new or malloc)
        this->field_C = 0;
        this->capacity = 0x10;               // initial capacity 16? (or size of something)
        return this;
    }
};