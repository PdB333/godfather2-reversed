// FUNC_NAME: InventoryManager::InventoryManager

undefined4 * __thiscall InventoryManager::InventoryManager(undefined4 *this, int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  this[1] = 0;
  *this = &PTR_FUN_00d78694;
  if (param_2 == 0) {
    param_2 = 0;
  }
  else {
    param_2 = param_2 + 0x48;
  }
  this[2] = param_2;
  this[3] = 0;
  if (param_2 != 0) {
    this[3] = *(undefined4 *)(param_2 + 4);
    *(undefined4 **)(param_2 + 4) = this + 2;
  }
  this[4] = 0;
  this[5] = 0;
  this[7] = 0;
  puVar3 = (undefined4 *)FUN_004eb390(0x30,0x10);
  uVar1 = _DAT_00d5780c;
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    puVar3[1] = 0;
    *puVar3 = &PTR_FUN_00e372b4;
    puVar3[8] = 0;
    puVar3[4] = uVar1;
    puVar3[5] = uVar1;
    puVar3[6] = uVar1;
    puVar3[7] = uVar1;
  }
  this[6] = puVar3;
  puVar3[1] = puVar3[1] + 1;
  puVar3 = (undefined4 *)FUN_004eb390(0x30,0x10);
  uVar1 = _DAT_00d5780c;
  if (puVar3 == (undefined4 *)0x0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    puVar3[1] = 0;
    *puVar3 = &PTR_FUN_00e372b4;
    puVar3[8] = 0;
    puVar3[4] = uVar1;
    puVar3[5] = uVar1;
    puVar3[6] = uVar1;
    puVar3[7] = uVar1;
  }
  uVar2 = DAT_00d5f204;
  this[8] = puVar3;
  puVar3[1] = puVar3[1] + 1;
  this[0xc] = 0;
  this[0xd] = uVar2;
  this[0xe] = 0;
  this[0xf] = uVar1;
  _memset(this + 0x36,0,0x98);
  *(undefined1 *)(this + 0x5c) = 0;
  _memset(this + 0x10,0,0x98);
  *(undefined1 *)((int)this + 0x171) = 0;
  return this;
}