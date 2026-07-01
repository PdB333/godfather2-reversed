// FUNC_NAME: ANPCBrain::constructor
undefined4 * __thiscall ANPCBrain::constructor(undefined4 *this, int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_00481610();  // likely some resource or handle allocation
  }
  FUN_0064d390(0,1);  // base class initialization
  *this = &PTR_LAB_00e317dc;  // vtable for base class
  this[6] = 0;  // +0x18: some null pointer
  FUN_00454a10(uVar1);  // maybe attach/assign the handle
  this[9] = 1;  // +0x24: some flag set to true
  *this = &PTR_LAB_00d6a828;  // vtable for this class
  this[10] = &PTR_LAB_00d6a6c4;  // +0x28: vtable or interface pointer
  this[0xc] = &LAB_0079b0e0;  // +0x30: function pointer (likely AI state/behavior handler)
  this[0xd] = 0;  // +0x34: null pointer
  this[5] = this + 10;  // +0x14: pointer to the interface at +0x28
  return this;
}