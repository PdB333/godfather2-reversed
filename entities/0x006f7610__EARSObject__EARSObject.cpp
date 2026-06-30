// FUNC_NAME: EARSObject::EARSObject
EARSObject * __fastcall EARSObject::EARSObject(EARSObject *this)
{
  // Set vtable pointer (likely to class-specific vtable)
  this->vtable = (void *)&PTR_FUN_00d60804;

  // Debug fill with magic constants
  this->field1 = 0xbadbadba;   // +0x04
  this->field2 = 0xbeefbeef;   // +0x08
  this->field3 = 0xeac15a55;   // +0x0C
  this->field4 = 0x91100911;   // +0x10

  // Call base class constructor (with two null arguments)
  FUN_006fbc40(0, 0);

  // Clear all debug fields and set initialization values
  this->field9 = 0;            // +0x24
  this->field4 = 0;            // +0x10
  this->field3 = 0;            // +0x0C
  this->field2 = 0;            // +0x08
  this->field1 = 0;            // +0x04
  this->fieldB = 0;            // +0x2C
  *(byte *)((uint)this + 0x30) = 0; // +0x30 (byte)
  this->fieldA = 0xFF;         // +0x28

  return this;
}