// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(SomeClass *this)
{
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d7358c; // +0x00: vtable pointer

  // Initialize member variables to 0
  this->field_0x04 = 0; // +0x04
  this->field_0x08 = 0; // +0x08
  this->field_0x0C = 0; // +0x0C
  this->field_0x10 = 0; // +0x10
  this->field_0x14 = 0; // +0x14
  this->field_0x18 = 0; // +0x18
  this->field_0x1C = 0; // +0x1C
  this->field_0x20 = 0; // +0x20

  // Initialize sentinel/magic values for debugging
  this->field_0x24 = 0xbadbadba; // +0x24: sentinel value
  this->field_0x28 = 0xbeefbeef; // +0x28: sentinel value
  this->field_0x2C = 0xeac15a55; // +0x2C: sentinel value
  this->field_0x30 = 0x91100911; // +0x30: sentinel value

  // Initialize remaining fields to 0
  this->field_0x34 = 0; // +0x34
  this->field_0x38 = 0; // +0x38
  this->field_0x3C = 0; // +0x3C
  this->field_0x40 = 0; // +0x40
  this->field_0x44 = 0; // +0x44
  this->field_0x48 = 0; // +0x48
}