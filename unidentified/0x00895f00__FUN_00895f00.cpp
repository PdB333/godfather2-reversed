// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)
{
  FUN_0046c590(param_2);
  *(undefined1 *)(this + 0x16) = 0; // +0x58: some byte field
  *this = &PTR_FUN_00d77a54; // vtable pointer
  this[0xf] = &PTR_LAB_00d77a44; // +0x3C: some pointer
  this[0x12] = &PTR_LAB_00d77a40; // +0x48: some pointer
  this[0x17] = 0; // +0x5C: some pointer
  *(undefined2 *)(this + 0x18) = 0; // +0x60: some short
  *(undefined2 *)((int)this + 0x62) = 0; // +0x62: some short
  this[0x19] = 0; // +0x64: some pointer
  *(undefined2 *)(this + 0x1a) = 0; // +0x68: some short
  *(undefined2 *)((int)this + 0x6a) = 0; // +0x6A: some short
  this[0x1b] = 0; // +0x6C: some pointer
  *(undefined2 *)(this + 0x1c) = 0; // +0x70: some short
  *(undefined2 *)((int)this + 0x72) = 0; // +0x72: some short
  return this;
}