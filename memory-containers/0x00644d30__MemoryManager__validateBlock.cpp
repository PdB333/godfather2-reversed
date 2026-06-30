// FUNC_NAME: MemoryManager::validateBlock
uint MemoryManager::validateBlock(int *param_1)
{
  LPCRITICAL_SECTION lpCriticalSection;
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  int unaff_EDI;
  
  lpCriticalSection = *(LPCRITICAL_SECTION *)(unaff_EDI + 0x4e8); // +0x4E8: critical section pointer
  if (lpCriticalSection != (LPCRITICAL_SECTION)0x0) {
    EnterCriticalSection(lpCriticalSection);
    lpCriticalSection[1].DebugInfo =
         (PRTL_CRITICAL_SECTION_DEBUG)((int)&(lpCriticalSection[1].DebugInfo)->Type + 1);
  }
  iVar1 = *(int *)(unaff_EDI + 0x470); // +0x470: recursion guard / validation depth
  uVar8 = 0;
  if (1 < iVar1) goto LAB_00644f21;
  *(int *)(unaff_EDI + 0x470) = iVar1 + 1;
  uVar2 = param_1[1]; // +0x04: block flags
  if ((uVar2 & 2) == 0) {
    iVar4 = FUN_00647e60(); // get current heap context
    uVar8 = (uint)(iVar4 == 0);
    if (uVar8 == 0) {
      uVar7 = uVar2 & 0x7ffffff8; // mask out low bits, get aligned size
      iVar5 = FUN_00647e60();
      uVar8 = (uint)(iVar5 != iVar4);
      if (uVar8 == 0) {
        uVar8 = 0;
        if ((uVar2 & 1) == 0) {
          iVar5 = FUN_00647e60();
          uVar8 = (uint)(iVar5 != iVar4);
          if (uVar8 != 0) goto LAB_00644f14;
        }
        if (((*(byte *)((int)param_1 + uVar7 + 4) & 1) != 0) ||
           (uVar7 = (uint)(*(uint *)((int)param_1 + uVar7) != uVar7), uVar8 = uVar8 + uVar7,
           uVar7 == 0)) goto LAB_00644e1b;
      }
    }
  }
  else {
LAB_00644e1b:
    uVar7 = uVar2 & 0x7ffffff8;
    if ((uVar2 & 2) == 0) {
      puVar6 = (undefined4 *)FUN_00647e60();
      piVar3 = (int *)*puVar6;
      uVar8 = ((uVar8 + (puVar6 == (undefined4 *)0x0) + (uint)(param_1 < piVar3)) -
              (uint)(param_1 < (int *)(puVar6[1] + (int)piVar3))) +
              (2 - (uint)((int *)(uVar7 + (int)param_1) < (int *)(puVar6[1] + (int)piVar3)));
      if (param_1 == *(int **)(unaff_EDI + 0x440)) { // +0x440: current allocation pointer
        if (((int *)param_1[2] == param_1) && ((int *)param_1[3] == param_1)) {
          iVar4 = 0;
        }
        else {
          iVar4 = 1;
        }
        iVar4 = uVar8 + iVar4 + (uint)(uVar7 < 0x10);
        uVar8 = (byte)~*(byte *)(param_1 + 1) & 1;
      }
      else {
        if (*(int *)(unaff_EDI + 0x464) != *(int *)(unaff_EDI + 0x460)) goto LAB_00644f14;
        iVar4 = uVar8 + (param_1 < piVar3);
        piVar3 = (int *)(puVar6[1] + -0x10 + (int)puVar6);
        if ((piVar3 < (int *)(uVar7 + (int)param_1)) && (param_1 != piVar3)) {
          uVar8 = 1;
        }
        else {
          uVar8 = 0;
        }
      }
      uVar8 = iVar4 + uVar8;
    }
    else {
      iVar4 = FUN_00647e60();
      uVar2 = *(int *)(unaff_EDI + 0x4d8) - 1; // +0x4D8: alignment mask
      uVar8 = uVar8 + (iVar4 != 0) + (uint)(((int)param_1 - *param_1 & uVar2) != 0) +
              (uint)(((int)param_1 + uVar7 + 0x10 & uVar2) != 0) + (uint)(((uint)param_1 & 7) != 0);
    }
  }
LAB_00644f14:
  *(int *)(unaff_EDI + 0x470) = iVar1;
LAB_00644f21:
  if (lpCriticalSection != (LPCRITICAL_SECTION)0x0) {
    lpCriticalSection[1].DebugInfo =
         (PRTL_CRITICAL_SECTION_DEBUG)((int)&lpCriticalSection[1].DebugInfo[-1].SpareWORD + 1);
    LeaveCriticalSection(lpCriticalSection);
  }
  return uVar8;
}