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
  FUN_0064d390(2,1);  // likely debug/logging call
  *this = &PTR_LAB_00e317dc;  // vtable pointer #1
  this[6] = 0;  // +0x18: some member initialized to 0
  FUN_00454a10(uVar1);  // likely sub-object constructor
  this[9] = 1;  // +0x24: some flag set to 1
  *this = &PTR_LAB_00d6a95c;  // vtable pointer #2 (overwrites previous)
  this[10] = &PTR_LAB_00d6a6c4;  // +0x28: another vtable or function pointer
  this[0xc] = &LAB_0079b110;  // +0x30: function pointer
  this[0xd] = 0;  // +0x34: member set to 0
  this[5] = this + 10;  // +0x14: pointer to self+0x28 (likely a linked list or iterator)
  return this;
}