// FUNC_NAME: Debug::Debug
undefined4 * __thiscall Debug::Debug(undefined4 *this, undefined4 param_2)
{
  baseClassConstructor(param_2); // FUN_0046c590
  this[0] = &PTR_FUN_00d5da30; // vtable pointer
  this[0xf] = &PTR_LAB_00d5da20; // secondary vtable or function pointer (offset 0x3C)
  this[0x12] = &PTR_LAB_00d5da1c; // another pointer (offset 0x48)
  this[0x14] = 0; // field at +0x50
  *(undefined2 *)(this + 0x15) = 0; // word at +0x54
  *(undefined2 *)((int)this + 0x56) = 0; // word at +0x56
  this[0x16] = 0; // +0x58
  *(undefined2 *)(this + 0x17) = 0; // +0x5C
  *(undefined2 *)((int)this + 0x5E) = 0; // +0x5E
  this[0x18] = 0; // +0x60
  *(undefined2 *)(this + 0x19) = 0; // +0x64
  *(undefined2 *)((int)this + 0x66) = 0; // +0x66
  this[0x1a] = 0xbadbadba; // debug magic signature (offset 0x68)
  this[0x1b] = 0xbeefbeef; // debug magic signature (offset 0x6C)
  this[0x1c] = 0xeac15a55; // debug magic signature (offset 0x70)
  this[0x1d] = 0x91100911; // debug magic signature (offset 0x74)
  *(undefined2 *)(this + 0x1e) = 0; // +0x78
  *(undefined2 *)((int)this + 0x7A) = 0; // +0x7A
  *(undefined2 *)(this + 0x1f) = 0; // +0x7C
  this[0x22] = 0; // +0x88
  this[0x23] = 0; // +0x8C
  this[0x24] = 0; // +0x90
  this[0x25] = 0; // +0x94
  *(undefined1 *)(this + 0x26) = 0; // byte at +0x98
  *(undefined1 *)((int)this + 0x99) = 0; // byte at +0x99
  *(undefined1 *)((int)this + 0x9A) = 0; // byte at +0x9A
  return this;
}