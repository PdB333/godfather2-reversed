// FUNC_NAME: EARSObject::EARSObject
// Function at 0x006eb310: Constructor for EARSObject (or derived class)
// Initializes vtable pointer, two function pointers, and zeros a large data block.

// Assumed base class or helper function; likely sets up base object fields
extern void EARSObject_baseInit(void* param);

class EARSObject {
public:
    // Virtual table pointer at offset +0x00
    void* vtable;

    // Function pointer at offset +0x3C (60)
    void* field_3C;

    // Function pointer at offset +0x48 (72)
    void* field_48;

    // Large zero-initialized region starting at offset +0x50 (80)
    // Layout:
    // +0x50: dword (index 0x14)
    // +0x54: short (low part of index 0x15)
    // +0x56: short (high part of index 0x15)
    // +0x58 to +0xCC: dwords (indices 0x16 through 0x33)
    // Total 128 bytes (32 ints) from +0x50 to +0xCF
};

// __thiscall constructor
void* __thiscall EARSObject::EARSObject(void* param_2) {
    // Call base initialization (likely parent constructor or setup routine)
    EARSObject_baseInit(param_2);

    // Set vtable pointer (virtual method table)
    this->vtable = (void*)0x00d5fe50; // PTR_FUN_00d5fe50

    // Set function pointers (probably state function or delegate pointers)
    this->field_3C = (void*)0x00d5fe40; // PTR_LAB_00d5fe40  (offset +0x3C)
    this->field_48 = (void*)0x00d5fe3c; // PTR_LAB_00d5fe3c  (offset +0x48)

    // Zero-initialize data region starting at +0x50 (size 128 bytes)
    // First zero the dword at offset +0x50 (index 0x14)
    *((uint32_t*)((char*)this + 0x50)) = 0;

    // Then zero the two shorts at offsets +0x54 and +0x56 (within index 0x15)
    *((uint16_t*)((char*)this + 0x54)) = 0;
    *((uint16_t*)((char*)this + 0x56)) = 0;

    // Zero the remaining dwords from offset +0x58 (index 0x16) to +0xCC (index 0x33)
    for (int i = 0x16; i <= 0x33; ++i) {
        ((uint32_t*)this)[i] = 0;
    }

    return this;
}