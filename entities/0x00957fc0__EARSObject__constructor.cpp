// FUNC_NAME: EARSObject::constructor
// Function address: 0x00957fc0
// Role: Constructor for EARSObject, initializes vtable, function tables, and zeroes fields.

#include <cstdint>

class EARSObject {
public:
    // +0x00: vtable pointer (PTR_FUN_00d8c42c)
    void* vtable;
    // +0x3C: pointer to function table (PTR_LAB_00d8c41c)
    void* field_0x3C;
    // +0x48: pointer to function table (PTR_LAB_00d8c418)
    void* field_0x48;
    // +0x50: integer
    int field_0x50;
    // +0x54: short
    int16_t field_0x54;
    // +0x56: short
    int16_t field_0x56;
    // +0x58: integer
    int field_0x58;
    // +0x5C: short
    int16_t field_0x5C;
    // +0x5E: short
    int16_t field_0x5E;
    // +0x60: integer
    int field_0x60;
    // +0x64: integer
    int field_0x64;
    // +0x68: integer
    int field_0x68;
    // +0x6C: integer
    int field_0x6C;

    // Constructor (called as __thiscall)
    void constructor(void* param_2);
};

// External base constructor call at 0x0046c590
// This likely initializes the base class portion.
// We'll keep it as a comment placeholder.

void EARSObject::constructor(void* param_2) {
    // Call base constructor (FUN_0046c590)
    // BaseClass::constructor(param_2);
    
    // Set vtable pointer
    this->vtable = reinterpret_cast<void*>(0x00d8c42c);
    
    // Set function table pointers
    this->field_0x3C = reinterpret_cast<void*>(0x00d8c41c);
    this->field_0x48 = reinterpret_cast<void*>(0x00d8c418);
    
    // Zero out the rest
    this->field_0x50 = 0;
    this->field_0x54 = 0;
    this->field_0x56 = 0;
    this->field_0x58 = 0;
    this->field_0x5C = 0;
    this->field_0x5E = 0;
    this->field_0x60 = 0;
    this->field_0x64 = 0;
    this->field_0x68 = 0;
    this->field_0x6C = 0;
}