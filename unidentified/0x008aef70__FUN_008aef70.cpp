// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_00481610();  // likely some allocation or initialization
  }
  FUN_0064d390(0,1);  // likely memory manager or debug function
  *this = &PTR_LAB_00e317dc;  // vtable pointer 1
  this[6] = 0;  // +0x18: some flag or pointer
  FUN_00454a10(uVar1);  // likely base class constructor
  this[9] = 1;  // +0x24: some count or flag
  *this = &PTR_LAB_00d7a178;  // vtable pointer 2 (overwrites previous)
  this[10] = &PTR_FUN_00d7a13c;  // +0x28: function pointer or vtable
  this[0xd] = 0;  // +0x34: null pointer
  this[0xc] = &LAB_008a8980;  // +0x30: function pointer or address
  this[0x10] = 0;  // +0x40: null
  this[0x11] = 0;  // +0x44: null
  this[0x12] = 0;  // +0x48: null
  this[5] = this + 10;  // +0x14: pointer to self+0x28 (likely a list or iterator)
  return this;
}