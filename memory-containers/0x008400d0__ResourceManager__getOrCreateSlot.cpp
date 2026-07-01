// FUNC_NAME: ResourceManager::getOrCreateSlot
int * __thiscall ResourceManager::getOrCreateSlot(int this, int index) {
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  if ((index < 0) || (*(int *)(this + 0x50) <= index)) {
    return 0;
  }
  iVar1 = this + 0x5c + index * 8;
  if (*(int *)(this + 0x5c + index * 8) != 0) {
    return (int *)iVar1;
  }
  iVar2 = FUN_0083fa50(index);
  if (iVar2 != 0) {
    uVar3 = FUN_004461c0(iVar2, 0);
    iVar2 = FUN_0045d9e0(uVar3);
    if (iVar2 != 0) {
      uVar3 = FUN_008e9ae0(uVar3);
      FUN_0083ff00(iVar2);
      *(undefined4 *)(iVar1 + 4) = uVar3;
      return (int *)iVar1;
    }
    return 0;
  }
  return 0;
}