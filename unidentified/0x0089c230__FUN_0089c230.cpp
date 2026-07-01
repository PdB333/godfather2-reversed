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
  FUN_0064d390(1,1); // likely a memory manager or debug function
  *this = &PTR_LAB_00e317dc; // vtable pointer 1
  this[6] = 0; // +0x18: some member initialized to 0
  FUN_00454a10(uVar1); // sub-object initialization
  this[9] = 2; // +0x24: some member set to 2
  *this = &PTR_LAB_00d78560; // vtable pointer 2 (overwrites previous)
  this[0xd] = 0; // +0x34: some member initialized to 0
  this[10] = &PTR_LAB_00d77e00; // +0x28: pointer to some static data
  this[0xc] = &LAB_0089a1b0; // +0x30: function pointer or vtable
  FUN_004a8ec0(0); // some initialization call
  this[5] = this + 10; // +0x14: pointer to this+0x28 (self-reference)
  return this;
}