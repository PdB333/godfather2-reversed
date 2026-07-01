// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass_constructor(undefined4 *this, int param_2)
{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_00481610(); // likely some allocation or initialization
  }
  FUN_0064d390(0,1); // likely a memory or debug function
  *this = &PTR_LAB_00e317dc; // vtable pointer 1
  this[6] = 0; // +0x18: some member set to 0
  FUN_00454a10(uVar1); // likely another initialization
  this[9] = 2; // +0x24: some member set to 2
  *this = &PTR_LAB_00d79e20; // vtable pointer 2 (overwrites previous)
  this[10] = &PTR_LAB_00d79ba0; // +0x28: pointer to another vtable or data
  this[0xc] = &LAB_008a8970; // +0x30: function pointer
  this[0xd] = 0; // +0x34: some member set to 0
  this[0xe] = &PTR_LAB_00e35c24; // +0x38: pointer to data
  this[0xf] = 0xffffffff; // +0x3c: set to -1
  this[0x10] = 0xffffffff; // +0x40: set to -1
  this[0x11] = 0; // +0x44: set to 0
  this[0x12] = 0xffffffff; // +0x48: set to -1
  this[0x13] = 0xffffffff; // +0x4c: set to -1
  this[0x14] = 0; // +0x50: set to 0
  this[0x15] = 0; // +0x54: set to 0
  this[5] = this + 10; // +0x14: pointer to self+0x28 (likely a list head)
  return this;
}