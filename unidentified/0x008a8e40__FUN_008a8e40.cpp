// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, int param_2)
{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_00481610();
  }
  FUN_0064d390(0,1);
  *this = &PTR_LAB_00e317dc; // vtable pointer 1
  this[6] = 0; // +0x18: some member initialized to 0
  FUN_00454a10(uVar1);
  this[9] = 1; // +0x24: some member initialized to 1
  *this = &PTR_LAB_00d79cc0; // vtable pointer 2 (overwrites previous)
  this[10] = &PTR_LAB_00d79ba0; // +0x28: pointer to another vtable or data
  this[0xc] = &LAB_008a8990; // +0x30: function pointer or address
  this[0xd] = 0; // +0x34: initialized to 0
  this[0xe] = &PTR_LAB_00e35c24; // +0x38: pointer to data
  this[0xf] = 0xffffffff; // +0x3c: initialized to -1
  this[0x10] = 0xffffffff; // +0x40: initialized to -1
  this[0x11] = 0; // +0x44: initialized to 0
  this[0x12] = 0xffffffff; // +0x48: initialized to -1
  this[0x13] = 0xffffffff; // +0x4c: initialized to -1
  this[0x14] = 0; // +0x50: initialized to 0
  this[0x15] = 0; // +0x54: initialized to 0
  this[5] = this + 10; // +0x14: pointer to self+0x28 (this[10])
  return this;
}