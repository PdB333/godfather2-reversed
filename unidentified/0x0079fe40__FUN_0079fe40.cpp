// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, int param_2)
{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_00481610(); // likely some allocation or initialization
  }
  FUN_0064d390(1,1); // likely a memory or debug function
  *this = &PTR_LAB_00e317dc; // vtable pointer 1
  this[6] = 0; // +0x18: some member set to 0
  FUN_00454a10(uVar1); // likely another initialization
  this[9] = 2; // +0x24: some member set to 2
  *this = &PTR_LAB_00d6a854; // vtable pointer 2 (overwrites previous)
  this[10] = &PTR_LAB_00d6a6dc; // +0x28: pointer to something
  this[0xc] = &LAB_0079b160; // +0x30: function pointer or vtable
  this[0xd] = 0; // +0x34: member set to 0
  this[5] = this + 10; // +0x14: pointer to self+0x28 (likely a list or iterator)
  return this;
}