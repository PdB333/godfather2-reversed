// FUNC_NAME: GameStateManager::constructor
undefined4 * __thiscall GameStateManager::constructor(undefined4 *this, undefined4 param_2)

{
  undefined4 uVar1;
  
  FUN_0046c590(param_2);
  uVar1 = DAT_00d5ef50;
  *this = &PTR_FUN_00d7d370;  // vtable pointer
  this[0xf] = &PTR_LAB_00d7d360;  // +0x3C
  this[0x12] = &PTR_LAB_00d7d35c;  // +0x48
  this[0x14] = 0;  // +0x50 - state flags
  *(undefined2 *)(this + 0x15) = 0;  // +0x54 - short field
  *(undefined2 *)((int)this + 0x56) = 0;  // +0x56 - another short
  this[0x16] = uVar1;  // +0x58 - some global state
  uVar1 = _DAT_00d5c458;
  this[0x17] = _DAT_00d5c458;  // +0x5C
  this[0x18] = uVar1;  // +0x60
  this[0x19] = uVar1;  // +0x64
  this[0x1a] = uVar1;  // +0x68
  this[0x1b] = uVar1;  // +0x6C
  return this;
}