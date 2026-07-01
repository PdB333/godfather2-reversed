// FUNC_NAME: NetworkManager::removeConnectionFromSlot
void __thiscall NetworkManager::removeConnectionFromSlot(int thisPtr, int *connectionArray, int param3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int local_8;
  int local_4;
  
  FUN_00792010(*(int *)(thisPtr + 0x30) + *(int *)(thisPtr + 0x24));
  piVar2 = connectionArray;
  iVar3 = connectionArray[4];
  local_8 = connectionArray[2];
  if (iVar3 == 0) {
    if (local_8 == 0) {
      connectionArray = (int *)connectionArray[3];
      uVar5 = 0;
      local_8 = DAT_01129904;
      if (*(int *)(thisPtr + 0x24) != 0) {
        iVar3 = 0;
        do {
          iVar1 = *(int *)(iVar3 + *(int *)(thisPtr + 0x20)); // +0x20: connectionSlots array
          if ((int *)iVar1 != connectionArray) {
            iVar4 = FUN_008c7510(iVar1); // getConnectionId
            iVar1 = *piVar2;
            if ((iVar4 == iVar1) || ((iVar4 != piVar2[1] && (iVar1 == 4)))) {
              local_4 = *(int *)(thisPtr + 0x20) + 4 + iVar3;
              FUN_00792410(&local_4); // removeFromSlot
            }
          }
          uVar5 = uVar5 + 1;
          iVar3 = iVar3 + 0x10;
        } while (uVar5 < *(uint *)(thisPtr + 0x24)); // +0x24: maxConnections
      }
    }
    else {
      connectionArray = (int *)iVar3;
      iVar3 = FUN_007923a0(&local_8); // findSlotByAddress
      if (-1 < iVar3) {
        param3 = iVar3 * 0x10 + 4 + *(int *)(thisPtr + 0x20); // +0x20: activeSlots offset
        FUN_00792410(&param3);
        return;
      }
    }
  }
  else {
    connectionArray = (int *)iVar3;
    iVar3 = FUN_007923a0(&connectionArray); // findSlotByKey
    if (-1 < iVar3) {
      param3 = iVar3 * 0x10 + 4 + *(int *)(thisPtr + 0x2c); // +0x2c: pendingSlots offset
      FUN_00792410(&param3);
      return;
    }
  }
  return;
}