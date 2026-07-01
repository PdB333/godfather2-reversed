// FUNC_NAME: SomeClass::Constructor
// Constructor for a class with multiple vtable pointers (multiple inheritance)
// param_2: bit 0 indicates whether to call a cleanup/deallocation function (likely heap allocation flag)
SomeClass* __thiscall SomeClass::Constructor(SomeClass* this, byte param_2)
{
    // Set vtable pointers for each base class / interface
    this->vtable0 = &PTR_FUN_00d7f470;   // +0x00
    this->vtable1 = &PTR_LAB_00d7f460;   // +0x3C (offset 0x0F * 4)
    this->vtable2 = &PTR_LAB_00d7f45c;   // +0x48 (offset 0x12 * 4)
    this->vtable3 = &PTR_LAB_00d7f458;   // +0x50 (offset 0x14 * 4)
    this->vtable4 = &PTR_LAB_00d7f3f8;   // +0x54 (offset 0x15 * 4)
    this->vtable5 = &PTR_LAB_00d7f390;   // +0x58 (offset 0x16 * 4)

    // Call base class constructor
    BaseClass::Constructor(this); // FUN_008dc180

    // If bit 0 of param_2 is set, call deallocation/cleanup (e.g., operator delete)
    if ((param_2 & 1) != 0)
    {
        // Deallocate memory for this object (size 0x210 = 528 bytes)
        operatorDelete(this, 0x210); // FUN_0043b960
    }

    return this;
}