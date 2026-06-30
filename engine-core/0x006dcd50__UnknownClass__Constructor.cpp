// FUNC_NAME: UnknownClass::Constructor
undefined4* __thiscall UnknownClass::Constructor(undefined4* this, byte param_2) {
  // vtable setup (offset +0x00)
  *this = &PTR_FUN_00d5f678;
  // Additional vtable pointers for multiple inheritance / interfaces
  this[0x0f] = &PTR_LAB_00d5f668;  // +0x3C
  this[0x12] = &PTR_LAB_00d5f664;  // +0x48
  this[0x14] = &PTR_LAB_00d5f660;  // +0x50

  // Clean up existing sub-objects if they exist
  if (this[0x1c] != 0) {  // +0x70
    FUN_004daf90(this + 0x1c);  // destructor for sub-object
  }
  if (this[0x1a] != 0) {  // +0x68
    FUN_004daf90(this + 0x1a);  // destructor for sub-object
  }

  // General initialization
  FUN_00473880();

  // If flag bit 0 is set, free the entire allocation (0x1C8 bytes)
  if ((param_2 & 1) != 0) {
    FUN_0043b960(this, 0x1c8);  // operator delete
  }

  return this;
}