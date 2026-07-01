// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 uVar1;
  
  FUN_0046e6b0(param_2,0x4000); // Likely some initialization with size 0x4000
  uVar1 = _DAT_00d5c458; // Global data reference
  this[0x61] = 0; // +0x184: some field set to 0
  *(undefined1 *)(this + 99) = 0; // +0x18C: byte field set to 0
  *this = &PTR_FUN_00d7d7f0; // vtable pointer
  this[0xf] = &PTR_LAB_00d7d7e0; // +0x3C: pointer
  this[0x12] = &PTR_LAB_00d7d7dc; // +0x48: pointer
  this[0x14] = &PTR_LAB_00d7d7d8; // +0x50: pointer
  this[0x15] = &PTR_LAB_00d7d778; // +0x54: pointer
  this[0x16] = &PTR_LAB_00d7d710; // +0x58: pointer
  *(undefined1 *)(this + 0x60) = 1; // +0x180: byte set to 1
  this[0x62] = uVar1; // +0x188: store global value
  return this;
}