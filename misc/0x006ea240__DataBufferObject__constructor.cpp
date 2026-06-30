// FUNC_NAME: DataBufferObject::constructor
// Function address: 0x006ea240
// Role: Constructor for an object that initializes a vtable, two function pointers, and zeroes a large data region,
//        then optionally copies a 0x8000-byte buffer from a global into offset 0x3C.
// Known classes: Possibly related to EARS resource/data management (e.g. BNKStreamManager or a custom node)

class DataBufferObject {
    // +0x00: vtable pointer (set to PTR_FUN_00d5fd1c)
    // +0x3C: pointer to function table or data (set to PTR_LAB_00d5fd0c)
    // +0x48: pointer to another function table (set to PTR_LAB_00d5fd08)
    // +0x50: reserved (zeroed)
    // +0x54: reserved
    // +0x58: reserved
    // +0x5C: reserved
    // +0x60: reserved
    // +0x64: reserved
    // +0x68: reserved
    // +0x6C: reserved
    // +0x70: reserved
    // +0x74: short (zeroed)
    // +0x76: short (zeroed)
    // +0x78: reserved (zeroed)
    // +0x7C: reserved
    // +0x80: reserved
    // +0x84: reserved
    // +0x88: reserved
};

// Base class constructor (unknown, likely initializes some common fields)
extern int __thiscall BaseClassConstructor(void *this, int param2);

// Function to copy data from global source into a buffer (likely memcpy style)
extern int __thiscall CopyBuffer(void *dest, void *src, int size);

// Global data pointer (may be a singleton or a resource handle)
extern void *gDataBufferSource; // = DAT_0120e93c

DataBufferObject * __thiscall DataBufferObject::constructor(DataBufferObject *this, int param2) {
    // Call base class constructor first
    BaseClassConstructor(this, param2);

    // Set vtable pointer to this class's virtual table
    this->vtable = &PTR_FUN_00d5fd1c;

    // Set two function pointer tables (likely for callbacks or virtual dispatch)
    this->field_0x3C = &PTR_LAB_00d5fd0c;  // +0x0F
    this->field_0x48 = &PTR_LAB_00d5fd08;  // +0x12

    // Zero out a range of fields from +0x50 to +0x88
    this->field_0x50 = 0;  // +0x14
    this->field_0x54 = 0;  // +0x15
    this->field_0x58 = 0;  // +0x16
    this->field_0x5C = 0;  // +0x17
    this->field_0x60 = 0;  // +0x18
    this->field_0x64 = 0;  // +0x19
    this->field_0x68 = 0;  // +0x1A
    this->field_0x6C = 0;  // +0x1B
    this->field_0x70 = 0;  // +0x1C
    *(short *)((int)this + 0x74) = 0; // +0x1D (short)
    *(short *)((int)this + 0x76) = 0; // +0x76
    this->field_0x78 = 0;  // +0x1E
    this->field_0x7C = 0;  // +0x1F
    this->field_0x80 = 0;  // +0x20
    this->field_0x84 = 0;  // +0x21
    this->field_0x88 = 0;  // +0x22

    // If the global data source is valid, copy a large block into the buffer at +0x3C
    if (gDataBufferSource != 0) {
        CopyBuffer(&this->field_0x3C, gDataBufferSource, 0x8000);
    }

    return this;
}