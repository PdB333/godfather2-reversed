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
  FUN_0064d390(1,1);
  *this = &PTR_LAB_00e317dc;  // vtable pointer
  this[6] = 0;  // +0x18: some flag/pointer
  FUN_00454a10(uVar1);
  this[9] = 1;  // +0x24: some count/flag
  *this = &PTR_LAB_00d6a8ac;  // vtable pointer (overwritten)
  this[10] = &PTR_LAB_00d6a70c;  // +0x28: pointer to vtable or data
  this[0xc] = &LAB_0079b180;  // +0x30: function pointer
  this[0xd] = 0;  // +0x34: null
  this[5] = this + 10;  // +0x14: pointer to self+0x28
  return this;
}