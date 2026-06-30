// FUNC_NAME: MemoryPool::initialize
void MemoryPool::initialize(int param_1)

{
  int iVar1;
  uint in_EAX;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iStack_24;
  int iStack_20;
  int iStack_18;
  undefined4 local_c;
  undefined4 local_8;
  int local_4;
  
  uVar2 = in_EAX >> 0x11;
  uVar10 = uVar2 * 0x20008 + 0xb498;
  puVar3 = (undefined4 *)FUN_009c8f80();
  local_c = 2;
  local_8 = 0x800;
  local_4 = 0;
  iVar4 = (**(code **)*puVar3)(uVar10 + param_1 * 8,&local_c);
  if (uVar2 * 0x20008 + iVar4 == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = FUN_004d00d0();
  }
  if (iStack_24 != 0) {
    puVar3 = (undefined4 *)(iVar4 + uVar2 * 0x20000);
    iStack_20 = iStack_24;
    iVar9 = iVar4;
    do {
      if (puVar3 == (undefined4 *)0x0) {
        puVar7 = (undefined4 *)0x0;
      }
      else {
        *puVar3 = 0;
        puVar3[1] = iVar9;
        puVar7 = puVar3;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)(iVar5 + 0x28));
      iVar8 = *(int *)(iVar5 + 0x24);
      iVar1 = *(int *)(iVar5 + 0x1c);
      if (iVar8 < iVar1) {
        iVar6 = *(int *)(iVar5 + 0x20) + iVar8;
        *(int *)(iVar5 + 0x24) = iVar8 + 1;
        if (iVar1 <= iVar6) {
          iVar6 = iVar6 - iVar1;
        }
        *(undefined4 **)(*(int *)(iVar5 + 0x18) + iVar6 * 4) = puVar7;
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)(iVar5 + 0x28));
      iVar9 = iVar9 + 0x20000;
      puVar3 = puVar3 + 2;
      iStack_20 = iStack_20 + -1;
      uVar10 = uVar2;
    } while (iStack_20 != 0);
  }
  iVar9 = iVar4 + iStack_18;
  iVar8 = 0x80;
  do {
    if (iVar9 == 0) {
      puVar3 = (undefined4 *)0x0;
    }
    else {
      puVar3 = (undefined4 *)FUN_004d1630();
      uVar10 = uVar2;
    }
    *puVar3 = 0;
    puVar3[1] = *(undefined4 *)(iVar5 + 0x60);
    if (*(undefined4 **)(iVar5 + 0x60) == (undefined4 *)0x0) {
      *(undefined4 **)(iVar5 + 0x5c) = puVar3;
    }
    else {
      **(undefined4 **)(iVar5 + 0x60) = puVar3;
    }
    iVar9 = iVar9 + 0x168;
    iVar8 = iVar8 + -1;
    *(undefined4 **)(iVar5 + 0x60) = puVar3;
  } while (iVar8 != 0);
  if (local_4 != 0) {
    puVar3 = (undefined4 *)(iVar4 + uVar10);
    do {
      if (puVar3 == (undefined4 *)0x0) {
        puVar7 = (undefined4 *)0x0;
      }
      else {
        *puVar3 = 0;
        puVar3[1] = 0;
        puVar7 = puVar3;
      }
      *puVar7 = *(undefined4 *)(iVar5 + 0x10);
      if (*(int *)(iVar5 + 0x10) == 0) {
        *(undefined4 **)(iVar5 + 0x14) = puVar7;
      }
      puVar3 = puVar3 + 2;
      local_4 = local_4 + -1;
      *(undefined4 **)(iVar5 + 0x10) = puVar7;
    } while (local_4 != 0);
  }
  *(int *)(iVar5 + 8) = iVar4;
  return;
}