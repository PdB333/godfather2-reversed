// FUNC_NAME: EARSObject::initOrConstructor
void __fastcall EARSObject::initOrConstructor(undefined4 *this)
{
  // Initialize all fields to 0
  this[0] = 0;   // +0x00: some pointer or handle
  this[1] = 0;   // +0x04
  this[2] = 0;   // +0x08
  this[3] = 0;   // +0x0C
  this[4] = 0;   // +0x10
  this[5] = 0;   // +0x14
  this[6] = 0;   // +0x18
  this[7] = 0;   // +0x1C
  this[8] = 0;   // +0x20
  this[9] = 0;   // +0x24
  this[0xB] = 0; // +0x2C
  this[0xC] = 0; // +0x30
  this[0xD] = 0; // +0x34
  this[0xE] = 0; // +0x38
  this[0x10] = 0;// +0x40
  this[0x11] = 0;// +0x44
  this[0x12] = 0;// +0x48
  this[0x13] = 0;// +0x4C
  this[0x15] = 0;// +0x54

  // Set self-pointers for linked list or parent references
  this[5] = this;  // +0x14: pointer to self
  this[10] = this; // +0x28: pointer to self
  this[0xF] = this;// +0x3C: pointer to self
  this[0x14] = this;// +0x50: pointer to self
}