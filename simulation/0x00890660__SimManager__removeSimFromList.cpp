// FUNC_NAME: SimManager::removeSimFromList
void __fastcall SimManager::removeSimFromList(SimManager *this)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_c;
  int *local_8;
  int local_4;

  iVar3 = this[0x70]; // +0x1C0: prevSim
  *this = &PTR_FUN_00d77360; // vtable
  this[0xf] = &PTR_LAB_00d77350; // +0x3C
  this[0x12] = &PTR_LAB_00d7734c; // +0x48
  this[0x14] = &PTR_LAB_00d77348; // +0x50
  this[0x15] = &PTR_LAB_00d772e8; // +0x54
  this[0x16] = &PTR_LAB_00d77280; // +0x58
  iVar4 = 0;
  if (iVar3 != 0) {
    *(int *)(iVar3 + 0x1c4) = this[0x71]; // +0x1C4: nextSim
    iVar3 = this[0x70]; // +0x1C0: prevSim
    iVar4 = iVar3;
  }
  if (this[0x71] != 0) { // +0x1C4: nextSim
    *(int *)(this[0x71] + 0x1c0) = iVar3; // +0x1C0: prevSim
    iVar4 = this[0x71]; // +0x1C4: nextSim
  }
  if (iVar4 != 0) {
    for (iVar3 = *(int *)(iVar4 + 0x1c0); iVar3 != 0; iVar3 = *(int *)(iVar3 + 0x1c0)) {
    }
    uVar4 = FUN_0088cfd0(); // getSimManager
    FUN_0088fbb0(uVar4); // updateSimList
  }
  iVar4 = DAT_0112e2dc; // global sim list
  iVar3 = *(int *)(*(int *)(this[0x4c] + 0x10) + 0x28); // +0x130: simType
  local_c = iVar3;
  FUN_008903b0(&local_8, &local_c); // findSimInList
  piVar1 = *(int **)(*(int *)(iVar4 + 4) + *(int *)(iVar4 + 8) * 4);
  if (local_8 != piVar1) {
    while (*local_8 == iVar3) {
      if ((int *)local_8[1] == this) {
        FUN_0088fe50(&local_8, local_8, local_4); // removeFromList
        if (*(int *)(DAT_0112e2dc + 0xc) == 0) { // list count
          FUN_008905b0(DAT_0112e2dc); // destroyList
        }
        break;
      }
      local_8 = (int *)local_8[2];
      while (local_8 == (int *)0x0) {
        piVar1 = (int *)(local_4 + 4);
        local_4 = local_4 + 4;
        local_8 = (int *)*piVar1;
      }
      if (local_8 == piVar1) break;
    }
  }
  if (this[0x73] != 0) { // +0x1CC: some resource
    FUN_009c8f10(this[0x73]); // releaseResource
    this[0x73] = 0;
    *(short *)(this + 0x72) = 0; // +0x1C8: resourceId
  }
  FUN_004b9fd0(); // memoryFree
  return;
}