// FUNC_NAME: Family::constructor

// Address: 0x008834d0
// Role: Family class constructor - initializes family color data and other properties.
// This function likely sets up a Family structure with default values for colors, sizes, and other display attributes.

#include <cstdint>

// Forward declarations
extern void BaseClassConstructor(uint32_t param2, uint32_t param3); // FUN_004ac120
extern uint32_t g_FamilyDefaultColor; // _DAT_00d5780c (e.g., white color 0xFFFFFFFF or float 1.0f)
extern void* g_FamilyVTable; // VTABLE at 0x00d76f6c

class Family {
public:
    // VTable pointer at +0x00
    void* vftable;
    
    // Fields starting at +0x50? Based on indices after vtable (indices 0x14 = offset 0x50)
    // Many are likely colors or vector components.
    // Indices are multiplied by 4 to get byte offset.
    
    // index 0x14 (offset 0x50)
    uint32_t field_0x50;
    // index 0x15 (offset 0x54)
    uint32_t field_0x54;
    // index 0x17 (offset 0x5C) - note out of order but we follow decompiled sequence
    uint32_t field_0x5C;
    // index 0x18 (offset 0x60)
    uint32_t field_0x60;
    // index 0x19 (offset 0x64)
    uint32_t field_0x64;
    // index 0x1A (offset 0x68)
    uint32_t field_0x68;
    // index 0x1B (offset 0x6C) - set to 6
    uint32_t familyType; // e.g., FamilyID (6 = neutral or max count)
    // index 0x1C (offset 0x70)
    uint32_t field_0x70;
    // index 0x1D (offset 0x74)
    uint32_t field_0x74;
    // index 0x1E (offset 0x78) - set to default
    uint32_t field_0x78;
    // index 0x20 (offset 0x80)
    uint32_t field_0x80;
    // index 0x21 (offset 0x84)
    uint32_t field_0x84;
    // index 0x22 (offset 0x88)
    uint32_t field_0x88;
    // index 0x23 (offset 0x8C)
    uint32_t field_0x8C;
    // index 0x24 (offset 0x90)
    uint32_t field_0x90;
    // index 0x25 (offset 0x94) - set to default
    uint32_t field_0x94;
    // index 0x26 (offset 0x98)
    uint32_t field_0x98;
    // index 0x27 (offset 0x9C)
    uint32_t field_0x9C;
    // index 0x28 (offset 0xA0)
    uint32_t field_0xA0;
    // index 0x29 (offset 0xA4)
    uint32_t field_0xA4;
    // index 0x2A (offset 0xA8) - set to default
    uint32_t field_0xA8;
    // index 0x2B (offset 0xAC)
    uint32_t field_0xAC;
    // index 0x2C (offset 0xB0)
    uint32_t field_0xB0;
    // index 0x2D (offset 0xB4)
    uint32_t field_0xB4;
    // index 0x2E (offset 0xB8)
    uint32_t field_0xB8;
    // index 0x2F (offset 0xBC) - set to default
    uint32_t field_0xBC;

    // Constructor
    Family* __thiscall constructor(uint32_t param2, uint32_t param3);
};

// Implementation
Family* __thiscall Family::constructor(uint32_t param2, uint32_t param3) {
    // Call base class constructor (e.g., GameObject or Entity)
    BaseClassConstructor(param2, param3);
    
    uint32_t defaultColor = g_FamilyDefaultColor; // Global default value (e.g., white color)
    
    // Set vtable
    this->vftable = &g_FamilyVTable;
    
    // Initialize fields to zero or default values
    this->field_0x50 = 0;
    this->field_0x54 = 0;
    this->field_0x5C = 0; // note out-of-order assignment in original, but logically it's here
    this->field_0x60 = 0;
    this->field_0x64 = 0;
    this->field_0x68 = 0;
    this->field_0x70 = 0;
    this->field_0x74 = 0;
    this->field_0x84 = 0; // index 0x21
    this->field_0x88 = 0; // index 0x22
    this->field_0x8C = 0; // index 0x23
    this->field_0x90 = 0; // index 0x24
    this->field_0x98 = 0; // index 0x26
    this->field_0x9C = 0; // index 0x27
    this->field_0xA0 = 0; // index 0x28
    this->field_0xA4 = 0; // index 0x29
    this->field_0xAC = 0; // index 0x2B
    this->field_0xB0 = 0; // index 0x2C
    this->field_0xB4 = 0; // index 0x2D
    this->field_0xB8 = 0; // index 0x2E
    
    // Set family type to 6 (likely representing a neutral or default family ID)
    this->familyType = 6;
    
    // Set multiple color/vector fields to the global default (e.g., white or identity)
    this->field_0x78 = defaultColor; // index 0x1E
    this->field_0x80 = defaultColor; // index 0x20
    this->field_0x94 = defaultColor; // index 0x25
    this->field_0xA8 = defaultColor; // index 0x2A
    this->field_0xBC = defaultColor; // index 0x2F
    
    return this;
}