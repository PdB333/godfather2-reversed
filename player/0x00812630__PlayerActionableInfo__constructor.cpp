// FUNC_NAME: PlayerActionableInfo::constructor
undefined4 * __thiscall PlayerActionableInfo::constructor(undefined4 *this, undefined4 param_2)

{
  FUN_0046c590(param_2);
  *this = &PTR_FUN_00d72ff4;
  this[0xf] = &PTR_LAB_00d72fe4;
  this[0x12] = &PTR_LAB_00d72fe0;
  this[0x14] = 0;           // +0x50: some pointer
  *(undefined2 *)(this + 0x15) = 0;     // +0x54: short
  *(undefined2 *)((int)this + 0x56) = 0; // +0x56: short
  this[0x16] = 0;           // +0x58: pointer
  *(undefined2 *)(this + 0x17) = 0;     // +0x5C: short
  *(undefined2 *)((int)this + 0x5E) = 0; // +0x5E: short
  this[0x18] = 0;           // +0x60: pointer
  *(undefined1 *)(this + 0x19) = 0;     // +0x64: byte
  *(undefined1 *)((int)this + 0x65) = 0; // +0x65: byte
  *(undefined1 *)((int)this + 0x66) = 0; // +0x66: byte
  *(undefined1 *)((int)this + 0x67) = 0; // +0x67: byte
  return this;
}