// FUNC_NAME: PlayerActionableInfo::constructor
undefined4 * __thiscall PlayerActionableInfo::constructor(undefined4 *this, int param_2)
{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_00481610(); // likely allocate or get some object reference
  }
  FUN_0064d390(0,1); // some vtable or flag initialization
  *this = &PTR_LAB_00e317dc; // +0x00: vtable pointer (base class)
  this[6] = 0; // +0x18: some flag or pointer (e.g., targetEntity?)
  FUN_00454a10(uVar1); // initialize from the object ref
  this[9] = 2; // +0x24: state or count (e.g., actionableType = 2)
  *this = &PTR_LAB_00d71f04; // +0x00: vtable pointer (derived class override)
  this[10] = &PTR_LAB_00d71d1c; // +0x28: another vtable or data pointer
  this[0xc] = &LAB_007fa6f0; // +0x30: function pointer or callback
  this[0xd] = 0; // +0x34: some flag or counter
  this[5] = this + 10; // +0x14: pointer to self+0x28 (e.g., an inner container or list)
  return this;
}