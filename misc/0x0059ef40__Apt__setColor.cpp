// FUNC_NAME: Apt::setColor
undefined1 Apt::setColor(undefined4 param_1, float r, float g, float b)
{
  int *piVar1;
  int *piVar2;
  code *pcVar3;
  bool bVar4;
  undefined1 uVar5;
  char cVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int unaff_FS_OFFSET;
  char *local_120;
  char *local_11c;
  undefined4 local_118;
  int local_114;
  undefined1 *local_110;
  int iStack_10c;
  char acStack_108 [260];
  
  piVar1 = *(int **)(unaff_FS_OFFSET + 0x2c);
  if (DAT_012055b0 == 0) {
    local_120 = "bAptIsInitialized";
    local_11c = "..\\source\\Apt\\Apt.cpp";
    local_118 = 0x24f;
    local_114 = 2;
    local_110 = &DAT_01128f44;
    if (DAT_01128f44 != '\0') {
      piVar2 = *(int **)(*piVar1 + 0x30);
      uVar7 = 1;
      if (((piVar2 == (int *)0x0) ||
          (uVar7 = (**(code **)(*piVar2 + 8))(&local_120,"bAptIsInitialized"),
          local_110 != (undefined1 *)0x0)) && ((uVar7 & 2) != 0)) {
        *local_110 = 0;
      }
      if (((piVar2 != (int *)0x0) || (local_114 != 4)) &&
         (((uVar7 & 1) != 0 || ((local_114 == 0 || (local_114 == 1)))))) {
        pcVar3 = (code *)swi(3);
        uVar5 = (*pcVar3)();
        return uVar5;
      }
    }
  }
  if ((r < DAT_00e2b05c) || (DAT_00e44584 < r)) {
    local_120 = "r >= 0.0f && r <= 255.f";
    local_11c = "..\\source\\Apt\\Apt.cpp";
    local_118 = 0x250;
    local_114 = 2;
    local_110 = &DAT_01128f45;
    if (DAT_01128f45 != '\0') {
      piVar2 = *(int **)(*piVar1 + 0x30);
      uVar7 = 1;
      if (((piVar2 == (int *)0x0) ||
          (uVar7 = (**(code **)(*piVar2 + 8))(&local_120,"r >= 0.0f && r <= 255.f"),
          local_110 != (undefined1 *)0x0)) && ((uVar7 & 2) != 0)) {
        *local_110 = 0;
      }
      if (((piVar2 != (int *)0x0) || (local_114 != 4)) &&
         (((uVar7 & 1) != 0 || ((local_114 == 0 || (local_114 == 1)))))) {
        pcVar3 = (code *)swi(3);
        uVar5 = (*pcVar3)();
        return uVar5;
      }
    }
  }
  if ((g < DAT_00e2b05c) || (DAT_00e44584 < g)) {
    local_120 = "g >= 0.0f && g <= 255.f";
    local_11c = "..\\source\\Apt\\Apt.cpp";
    local_118 = 0x251;
    local_114 = 2;
    local_110 = &DAT_01128f46;
    if (DAT_01128f46 != '\0') {
      piVar2 = *(int **)(*piVar1 + 0x30);
      uVar7 = 1;
      if (((piVar2 == (int *)0x0) ||
          (uVar7 = (**(code **)(*piVar2 + 8))(&local_120,"g >= 0.0f && g <= 255.f"),
          local_110 != (undefined1 *)0x0)) && ((uVar7 & 2) != 0)) {
        *local_110 = 0;
      }
      if (((piVar2 != (int *)0x0) || (local_114 != 4)) &&
         (((uVar7 & 1) != 0 || ((local_114 == 0 || (local_114 == 1)))))) {
        pcVar3 = (code *)swi(3);
        uVar5 = (*pcVar3)();
        return uVar5;
      }
    }
  }
  if ((b < DAT_00e2b05c) || (DAT_00e44584 < b)) {
    local_120 = "b >= 0.0f && b <= 255.f";
    local_11c = "..\\source\\Apt\\Apt.cpp";
    local_118 = 0x252;
    local_114 = 2;
    local_110 = &DAT_01128f47;
    if (DAT_01128f47 != '\0') {
      piVar1 = *(int **)(*piVar1 + 0x30);
      uVar7 = 1;
      if (((piVar1 == (int *)0x0) ||
          (uVar7 = (**(code **)(*piVar1 + 8))(&local_120,"b >= 0.0f && b <= 255.f"),
          local_110 != (undefined1 *)0x0)) && ((uVar7 & 2) != 0)) {
        *local_110 = 0;
      }
      if (((piVar1 != (int *)0x0) || (local_114 != 4)) &&
         (((uVar7 & 1) != 0 || ((local_114 == 0 || (local_114 == 1)))))) {
        pcVar3 = (code *)swi(3);
        uVar5 = (*pcVar3)();
        return uVar5;
      }
    }
  }
  bVar4 = false;
  uVar8 = FUN_0059e2f0();
  iVar9 = FUN_005aea60(uVar8,0,param_1,1,1);
  if (iVar9 != 0) {
    cVar6 = FUN_0059c5c0(0);
    if (cVar6 != '\0') {
      iVar9 = FUN_0059c3b0();
      if (iVar9 == 0) {
        local_120 = "pCIH";
        local_11c = "..\\source\\Apt\\Apt.cpp";
        local_118 = 0x25b;
        local_114 = 2;
        local_110 = &DAT_01128f48;
        FUN_0059bf00();
      }
      FUN_005b5d20();
      *(undefined1 *)(iVar9 + 100) = 0;
      *(float *)(*(int *)(iVar9 + 0x50) + 0x20) = r;
      *(float *)(iVar9 + 0x24) = r * DAT_00e44640;
      FUN_005b5d20();
      *(undefined1 *)(iVar9 + 100) = 0;
      *(float *)(*(int *)(iVar9 + 0x50) + 0x24) = g;
      *(float *)(iVar9 + 0x28) = g * DAT_00e44640;
      FUN_005b5d20();
      *(float *)(*(int *)(iVar9 + 0x50) + 0x28) = b;
      *(float *)(iVar9 + 0x2c) = b * DAT_00e44640;
      *(undefined4 *)(iVar9 + 0x14) = 0;
      *(undefined4 *)(iVar9 + 0x18) = 0;
      *(undefined4 *)(iVar9 + 0x1c) = 0;
      *(undefined1 *)(iVar9 + 100) = 1;
      return true;
    }
    cVar6 = FUN_0059c500();
    if (cVar6 != '\0') {
      iVar9 = FUN_0059c450();
      if (iVar9 == 0) {
        local_120 = "pArray";
        local_11c = "..\\source\\Apt\\Apt.cpp";
        local_118 = 0x268;
        local_114 = 2;
        local_110 = &DAT_01128f49;
        FUN_0059bf00();
      }
      iVar10 = FUN_005ab7b0(iVar9,uVar8);
      if (iVar10 != 0) {
        bVar4 = true;
        iStack_10c = FUN_005a8fe0();
        iVar10 = 0;
        if (0 < iStack_10c) {
          do {
            iVar11 = DAT_0119cbbc;
            if (((-1 < iVar10) && (iVar10 < *(int *)(iVar9 + 0x54))) &&
               (*(int *)(*(int *)(iVar9 + 0x4c) + iVar10 * 4) != 0)) {
              iVar11 = *(int *)(*(int *)(iVar9 + 0x4c) + iVar10 * 4);
            }
            if (iVar11 != 0) {
              acStack_108[0] = '\0';
              FUN_005a90a0(acStack_108,0x100);
              if (acStack_108[0] != '\0') {
                cVar6 = FUN_0059ef40(acStack_108,r,g,b);
                if ((cVar6 == '\0') || (!bVar4)) {
                  bVar4 = false;
                }
                else {
                  bVar4 = true;
                }
              }
            }
            iVar10 = iVar10 + 1;
          } while (iVar10 < iStack_10c);
        }
      }
    }
  }
  return bVar4;
}