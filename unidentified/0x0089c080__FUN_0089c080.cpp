// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, int param_2)
{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_00481610(); // likely some allocation or resource acquisition
  }
  FUN_0064d390(1,1); // likely a debug/logging function
  *this = &PTR_LAB_00e317dc; // vtable pointer set
  this[6] = 0; // +0x18: some member initialized to 0
  FUN_00454a10(uVar1); // likely initialization with the acquired resource
  this[9] = 1; // +0x24: some flag or counter set to 1
  *this = &PTR_LAB_00d78534; // vtable pointer updated (likely derived class)
  this[10] = &PTR_LAB_00d77de8; // +0x28: pointer to some static data
  this[0xc] = &LAB_0089a1d0; // +0x30: function pointer or another vtable
  this[0xd] = 0; // +0x34: member set to 0
  this[5] = this + 10; // +0x14: pointer to self + 0x28 (likely a linked list or iterator)
  return this;
}