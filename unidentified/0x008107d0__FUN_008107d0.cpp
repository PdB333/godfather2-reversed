// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 uVar1;
  
  FUN_0046c590(param_2);
  this[0x14] = &PTR_LAB_00e32854;
  uVar1 = _DAT_00d5780c;
  *this = &PTR_FUN_00d72e9c; // vtable pointer
  this[0xf] = &PTR_LAB_00d72e8c;
  this[0x12] = &PTR_LAB_00d72e88;
  this[0x14] = &PTR_LAB_00d72e84;
  this[0x15] = 0xbadbadba; // magic constant
  this[0x18] = 0x91100911; // magic constant
  this[0x16] = 0xbeefbeef; // magic constant
  this[0x17] = 0xeac15a55; // magic constant
  this[0x1c] = 0x91100911; // magic constant
  this[0x19] = 0xbadbadba; // magic constant
  this[0x1a] = 0xbeefbeef; // magic constant
  this[0x1b] = 0xeac15a55; // magic constant
  this[0x1d] = 0; // +0x74
  *(undefined2 *)(this + 0x1e) = 0; // +0x78
  *(undefined2 *)((int)this + 0x7a) = 0; // +0x7A
  this[0x1f] = 0; // +0x7C
  *(undefined2 *)(this + 0x20) = 0; // +0x80
  *(undefined2 *)((int)this + 0x82) = 0; // +0x82
  this[0x37] = 0; // +0xDC
  this[0x38] = 0; // +0xE0
  this[0x39] = 0; // +0xE4
  this[0x3a] = 0; // +0xE8
  this[0x3b] = 0; // +0xEC
  this[0x24] = uVar1; // +0x90
  this[0x25] = 0; // +0x94
  this[0x26] = 0; // +0x98
  this[0x27] = 0; // +0x9C
  this[0x28] = 0; // +0xA0
  this[0x29] = uVar1; // +0xA4
  this[0x2a] = 0; // +0xA8
  this[0x2b] = 0; // +0xAC
  this[0x2c] = 0; // +0xB0
  this[0x2d] = 0; // +0xB4
  this[0x2e] = uVar1; // +0xB8
  this[0x2f] = 0; // +0xBC
  this[0x30] = 0; // +0xC0
  this[0x31] = 0; // +0xC4
  this[0x32] = 0; // +0xC8
  this[0x33] = uVar1; // +0xCC
  this[0x36] = 0; // +0xD8
  this[0x35] = 0; // +0xD4
  this[0x34] = 0; // +0xD0
  return this;
}