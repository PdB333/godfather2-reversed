// FUNC_NAME: GodfatherGameObject::GodfatherGameObject
GodfatherGameObject::GodfatherGameObject(undefined4 param1) {
    // Offset 0x00: base class destructor vtable
    *this = &PTR_FUN_00e330c0;

    // Call base class constructor (likely for a parent or embedded object)
    FUN_0046c590(param1);

    // Offset 0x3C: secondary vtable pointer for first base class
    this->secondaryVtable1 = &PTR_LAB_00e330dc;

    // Offset 0x48: secondary vtable pointer for second base class
    this->secondaryVtable2 = &PTR_LAB_00e330ec;

    // Initialize many fields to 0
    // The pattern below clears individual 4-byte fields split into two 2-byte writes
    this->field_0x50 = 0;               // +0x50: 4-byte field
    *(int16_t*)((int)this + 0x54) = 0; // +0x54: low word
    *(int16_t*)((int)this + 0x56) = 0; // +0x56: high word (together 4 bytes at +0x54)

    this->field_0x5C = 0;               // +0x5C: 4-byte field
    *(int16_t*)((int)this + 0x60) = 0; // +0x60: low word
    *(int16_t*)((int)this + 0x62) = 0; // +0x62: high word

    this->field_0x6C = 0;               // +0x6C
    *(int16_t*)((int)this + 0x70) = 0; // +0x70
    *(int16_t*)((int)this + 0x72) = 0; // +0x72

    this->field_0x7C = 0;               // +0x7C
    *(int16_t*)((int)this + 0x80) = 0; // +0x80
    *(int16_t*)((int)this + 0x82) = 0; // +0x82

    this->field_0x8C = 0;               // +0x8C
    *(int16_t*)((int)this + 0x90) = 0; // +0x90
    *(int16_t*)((int)this + 0x92) = 0; // +0x92

    this->field_0x9C = 0;               // +0x9C
    *(int16_t*)((int)this + 0xA0) = 0; // +0xA0
    *(int16_t*)((int)this + 0xA2) = 0; // +0xA2

    this->field_0xAC = 0;               // +0xAC
    *(int16_t*)((int)this + 0xB0) = 0; // +0xB0
    *(int16_t*)((int)this + 0xB2) = 0; // +0xB2

    this->field_0xBC = 0;               // +0xBC
    *(int16_t*)((int)this + 0xC0) = 0; // +0xC0
    *(int16_t*)((int)this + 0xC2) = 0; // +0xC2

    this->field_0xCC = 0;               // +0xCC
    *(int16_t*)((int)this + 0xD0) = 0; // +0xD0
    *(int16_t*)((int)this + 0xD2) = 0; // +0xD2

    this->field_0xD8 = 0;               // +0xD8

    // Loop clears pairs of 4-byte fields with 16-byte stride
    // Each iteration sets two indices: i and i+3 (in 4-byte units)
    // Indices: 0x16, 0x1A, 0x1E, 0x22, 0x26, 0x2A, 0x2E, 0x32
    // Corresponding offsets: +0x58, +0x68, +0x78, +0x88, +0x98, +0xA8, +0xB8, +0xC8
    // Each sets two 4-byte fields: first at +offset, second at +offset+0xC
    for (undefined4* puVar1 = this + 0x16; puVar1 != this + 0x36; puVar1 += 4) {
        *puVar1 = 0;        // Clear field at puVar1 index
        puVar1[3] = 0;      // Clear field 3 indices later (12 bytes ahead)
    }

    return this;
}