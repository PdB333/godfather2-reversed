// FUNC_NAME: SomeClass::copyFrom
// Reconstructed copy constructor/assignment for a class with vtable at offset 0x24
// Size: 0x2E bytes (46 bytes)
// Layout: 11 uint32 fields (including vtable at offset 0x24), then 2 bytes at offsets 0x2C,0x2D
void __thiscall SomeClass::copyFrom(SomeClass *this, const SomeClass *src)
{
    // Copy the first 11 uint32 fields (offsets 0x00 to 0x28)
    this->field_0 = src->field_0;
    this->field_4 = src->field_4;
    this->field_8 = src->field_8;
    this->field_C = src->field_C;
    this->field_10 = src->field_10;
    this->field_14 = src->field_14;
    this->field_18 = src->field_18;
    this->field_1C = src->field_1C;
    this->field_20 = src->field_20;
    // Set vtable pointer to a fixed global vtable (LAB_00d5d708)
    this->vtable = (void *)0x00d5d708;
    this->field_28 = src->field_28;
    // Copy the two bytes at offsets 0x2C and 0x2D
    this->byte_2C = src->byte_2C;
    this->byte_2D = src->byte_2D;
    return;
}