// FUNC_NAME: SomeClass::constructor
// Address: 0x008cc220
// Role: Constructor for a class derived from a base (via FUN_004b60f0), setting up multiple vtable pointers.

#include <cstdint>

class SomeClass {
public:
    // Virtual function table pointers (multiple inheritance)
    void** vtable0;       // +0x00
    uint32_t field_0x04;  // offset 0x04, not set in this constructor
    uint32_t field_0x08;  // offset 0x08
    void** vtable0xC;     // +0x0C
    uint32_t field_0x10;  // offset 0x10
    uint32_t field_0x14;
    uint32_t field_0x18;
    uint32_t field_0x1C;
    uint32_t field_0x20;
    uint32_t field_0x24;
    uint32_t field_0x28;
    void** vtable0x2C;    // +0x2C (initially purecall, then overridden)
    uint32_t field_0x30;  // +0x30
    uint32_t field_0x34;  // +0x34
    uint32_t field_0x38;  // +0x38
    // ... more fields

    SomeClass(uint32_t param2, uint32_t param3) {
        // Call base class constructor
        FUN_004b60f0(param2, param3);

        // Initialize vtable pointers (vtable entries defined in data section)
        this->vtable0x2C = &PTR___purecall_00e3924c; // temporary purecall vtable
        this->vtable0 = &PTR_FUN_00d7c488;
        this->vtable0xC = &PTR_LAB_00d7c474;
        this->vtable0x2C = &PTR_FUN_00d7c460;        // actual vtable after base init
        this->field_0x30 = 0;
        this->field_0x38 = 0;
    }
};