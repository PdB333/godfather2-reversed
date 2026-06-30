// FUNC_NAME: CompositeObject::constructor
undefined4 * __fastcall CompositeObject::constructor(CompositeObject *this)
{
  // Calls base class constructor for initial part of object
  FUN_004737b0();  // Likely BaseClass1::BaseClass1()

  // Set vtable pointer for the primary class
  this->vtable = &PTR_FUN_00d5f758;

  // Set vtable pointer for secondary base class at offset +0x3C (0xF * 4)
  this->base2_vtable = &PTR_LAB_00d5f748;

  // Set vtable pointer for tertiary base class at offset +0x48 (0x12 * 4)
  this->base3_vtable = &PTR_LAB_00d5f744;

  // Set another vtable pointer at offset +0x50 (0x14 * 4)
  this->base4_vtable = &PTR_LAB_00d5f740;

  // Initialize fields at offsets +0x58, +0x5C, +0x60, +0x64 to zero
  this->field_0x58 = 0;
  this->field_0x5C = 0;
  this->field_0x60 = 0;
  this->field_0x64 = 0;

  // Call second base class constructor or additional initialization
  FUN_006e01d0();  // Likely BaseClass2::BaseClass2()

  return this;
}