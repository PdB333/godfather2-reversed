// FUNC_NAME: PlayerActionableInfo::constructor
undefined4 * __thiscall PlayerActionableInfo::constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 uVar1;
  undefined4 uVar2;
  
  FUN_0046c590(param_2); // Base class constructor call
  uVar2 = DAT_00d5ef50; // Some global value
  uVar1 = _DAT_00d5780c; // Another global value
  
  *this = &PTR_FUN_00d7d6bc; // vtable pointer
  this[0xf] = &PTR_LAB_00d7d6ac; // +0x3C - function pointer table
  this[0x12] = &PTR_LAB_00d7d6a8; // +0x48 - function pointer table
  this[0x14] = 0; // +0x50 - initialized to 0
  *(undefined2 *)(this + 0x15) = 0; // +0x54 - 2 bytes zeroed
  *(undefined2 *)((int)this + 0x56) = 0; // +0x56 - 2 bytes zeroed
  this[0x16] = uVar2; // +0x58 - set from global
  uVar2 = _DAT_00d5c458; // Another global value
  this[0x17] = _DAT_00d5c458; // +0x5C - set from global
  this[0x1c] = uVar2; // +0x70 - set from global
  this[0x1d] = uVar2; // +0x74 - set from global
  this[0x1e] = uVar2; // +0x78 - set from global
  this[0x1f] = uVar1; // +0x7C - set from global
  this[0x18] = uVar2; // +0x60 - set from global
  this[0x19] = uVar2; // +0x64 - set from global
  this[0x1a] = uVar2; // +0x68 - set from global
  this[0x1b] = uVar2; // +0x6C - set from global
  this[0x20] = uVar2; // +0x80 - set from global
  this[0x22] = uVar1; // +0x88 - set from global
  this[0x21] = uVar2; // +0x84 - set from global
  this[0x23] = uVar1; // +0x8C - set from global
  return this;
}