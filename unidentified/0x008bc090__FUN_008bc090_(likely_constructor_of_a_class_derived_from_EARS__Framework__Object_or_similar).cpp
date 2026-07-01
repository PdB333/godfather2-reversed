// FUNC_NAME: FUN_008bc090 (likely constructor of a class derived from EARS::Framework::Object or similar)
undefined4 * __thiscall FUN_008bc090(undefined4 *this, byte flags)
{
  // Set vtable pointer (derived class)
  this[0] = &PTR_FUN_00d7bac0;

  // Initialize various virtual method table pointers (function pointers)
  this[0xf] = &PTR_LAB_00d7bab0;   // +0x3C - likely vtable for interface 1
  this[0x12] = &PTR_LAB_00d7baac;   // +0x48 - vtable for interface 2
  this[0x14] = &PTR_LAB_00d7baa8;   // +0x50 - vtable for interface 3
  this[0x15] = &PTR_LAB_00d7ba48;   // +0x54 - vtable for interface 4
  this[0x16] = &PTR_LAB_00d7b9e0;   // +0x58 - vtable for interface 5
  this[0x60] = &PTR_LAB_00d7b9c8;   // +0x180 - vtable for interface 6

  // Call base class constructor
  FUN_008ba520();

  // If the lower bit of flags is set, allocate/construct additional memory
  if ((flags & 1) != 0) {
    // This appears to be an allocation/placement new call with size 0x2C0 (704 bytes)
    // param1 = this, param2 = size
    FUN_0043b960(this, 0x2c0);
  }

  return this;
}