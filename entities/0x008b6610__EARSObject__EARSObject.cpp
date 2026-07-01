// FUNC_NAME: EARSObject::EARSObject
// Function address: 0x008b6610
// Constructor for base object with debug sentinels and multiple vtable pointers.

void * __thiscall EARSObject::EARSObject(EARSObject *this, void *param_2)
{
    // Call base constructor at 0x0046c590
    baseConstructor(param_2);

    // Initialize primary vtable pointer
    this->vftable = (void *)(*PTR_FUN_00d7b104);  // +0x00

    // Initialize secondary vtable pointers (multiple inheritance or interfaces)
    this->base1Vftable = (void *)(*PTR_LAB_00d7b0f4); // +0x3C
    this->base2Vftable = (void *)(*PTR_LAB_00d7b0f0); // +0x48

    // Clear short fields (likely flags or padding)
    *(uint16_t *)((uint8_t *)this + 0x54) = 0;   // +0x54
    *(uint16_t *)((uint8_t *)this + 0x56) = 0;   // +0x56
    *(uint16_t *)((uint8_t *)this + 0x5C) = 0;   // +0x5C
    *(uint16_t *)((uint8_t *)this + 0x5E) = 0;   // +0x5E

    // First sentinel block (debug marker)
    this->magicStart[0] = 0xBADBADBA; // +0x60
    this->magicStart[1] = 0xBEEFBEEF; // +0x64
    this->magicStart[2] = 0xEAC15A55; // +0x68
    this->magicStart[3] = 0x91100911; // +0x6C

    // Padding/refcount fields between sentinel blocks
    this->field_0x70 = 0; // +0x70
    this->field_0x74 = 0; // +0x74

    // Second sentinel block
    this->magicEnd[0] = 0xBADBADBA; // +0x78
    this->magicEnd[1] = 0xBEEFBEEF; // +0x7C
    this->magicEnd[2] = 0xEAC15A55; // +0x80
    this->magicEnd[3] = 0x91100911; // +0x84

    // Trailing zero fields
    this->field_0x88 = 0; // +0x88
    this->field_0x8C = 0; // +0x8C

    // Late-initialized fields at offset 0x50 and 0x58
    this->field_0x50 = 0; // +0x50
    this->field_0x58 = 0; // +0x58

    return this;
}