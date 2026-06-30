// FUNC_NAME: SimNpc::processActionCommand
void SimNpc::processActionCommand(int param_1, short *param_2, int param_3)

{
  int *piVar1;
  byte bVar2;
  undefined4 *puVar3;
  uint uVar4;
  code *pcVar5;
  char cVar6;
  undefined1 uVar7;
  short *psVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  int *piVar12;
  int *local_50c;
  int *local_508;
  undefined4 local_504;
  int *local_500;
  undefined1 local_4fc [8];
  int local_4f4;
  undefined1 local_4f0 [4];
  undefined4 *local_4ec;
  undefined1 auStack_278 [632];
  
  piVar11 = (int *)0x0;
  FUN_0064b9e0(0x40,local_4fc);
  local_4f4 = FUN_00655250();
  if ((local_4f4 != 0) && (cVar6 = FUN_00654910(), cVar6 != '\0')) {
    FUN_00656440(param_1);
    return;
  }
  piVar12 = *(int **)(param_1 + 0x24);
  local_508 = (int *)0x0;
  local_50c = piVar12;
  if (0 < (int)piVar12) {
    local_500 = *(int **)(param_1 + 0x2c);
    do {
      piVar11 = (int *)*local_500;
      if (((piVar11[0x6d] == 2) && ((char)piVar11[100] == '\0')) &&
         (cVar6 = FUN_006549b0(), cVar6 == '\0')) {
        iVar9 = piVar11[0x61];
        iVar10 = 0;
        if (0 < iVar9) {
          psVar8 = (short *)piVar11[99];
          do {
            if (((*param_2 == *psVar8) && (*(int *)(param_2 + 2) == *(int *)(psVar8 + 2))) &&
               ((*(int *)(param_2 + 4) == *(int *)(psVar8 + 4) &&
                ((*(int *)(param_2 + 6) == *(int *)(psVar8 + 6) &&
                 (*(int *)(param_2 + 8) == *(int *)(psVar8 + 8))))))) break;
            iVar10 = iVar10 + 1;
            psVar8 = psVar8 + 10;
          } while (iVar10 < iVar9);
        }
        piVar12 = local_50c;
        if (iVar10 != iVar9) break;
      }
      local_508 = (int *)((int)local_508 + 1);
      local_500 = local_500 + 1;
    } while ((int)local_508 < (int)piVar12);
  }
  if (local_508 == piVar12) {
    return;
  }
  FUN_0065a5e0(local_4f0);
  cVar6 = FUN_0064ca10(param_3,local_4f0);
  if (cVar6 == '\0') {
    if (local_4ec == (undefined4 *)0x0) {
      return;
    }
    do {
      puVar3 = (undefined4 *)local_4ec[2];
      *local_4ec = 0;
      local_4ec[1] = 0;
      local_4ec[2] = 0;
      local_4ec = puVar3;
    } while (puVar3 != (undefined4 *)0x0);
    return;
  }
  *(uint *)(param_3 + 0x18) = *(int *)(param_3 + 0x18) + 7U & 0xfffffff8;
  FUN_0064b9e0(0x40,local_4fc);
  cVar6 = FUN_006549b0();
  if (cVar6 != '\0') {
    if (local_4ec == (undefined4 *)0x0) {
      return;
    }
    do {
      puVar3 = (undefined4 *)local_4ec[2];
      *local_4ec = 0;
      local_4ec[1] = 0;
      local_4ec[2] = 0;
      local_4ec = puVar3;
    } while (puVar3 != (undefined4 *)0x0);
    return;
  }
  uVar4 = *(uint *)(param_3 + 0x18);
  if (*(uint *)(param_3 + 0x2c) < uVar4) {
    *(undefined1 *)(param_3 + 0x1c) = 1;
  }
  else {
    bVar2 = *(byte *)((uVar4 >> 3) + *(int *)(param_3 + 0xc));
    *(uint *)(param_3 + 0x18) = uVar4 + 1;
    local_50c = piVar11;
    if ((bVar2 & (byte)(1 << ((byte)uVar4 & 7))) != 0) {
      if (*(int *)(param_1 + 0x30) == 0) goto LAB_0065768d;
      *(undefined1 *)((int)piVar11 + 0x131) = 1;
      iVar9 = FUN_009c8e50(0x24);
      if (iVar9 == 0) {
        iVar9 = 0;
      }
      else {
        iVar9 = FUN_00654840(param_3);
      }
      piVar12 = (int *)piVar11[0x54];
      if (piVar12 != (int *)0x0) {
        piVar1 = piVar12 + 2;
        *piVar1 = *piVar1 + -1;
        if (*piVar1 == 0) {
          (**(code **)(*piVar12 + 8))();
        }
      }
      piVar11[0x54] = iVar9;
      if (iVar9 != 0) {
        *(int *)(iVar9 + 8) = *(int *)(iVar9 + 8) + 1;
      }
      FUN_00657960();
      *(uint *)(param_3 + 0x18) = *(int *)(param_3 + 0x18) + 7U & 0xfffffff8;
      FUN_0065e570(piVar11[0x55],&local_50c,piVar11[0x54]);
      FUN_006544b0();
      if ((local_50c != (int *)0x0) && (local_50c[2] = local_50c[2] + -1, local_50c[2] == 0)) {
        (**(code **)(*local_50c + 8))();
      }
      FUN_0065a5e0(auStack_278);
      cVar6 = FUN_0064ca10(param_3,auStack_278);
      if (cVar6 == '\0') {
        FUN_00656aa0();
        goto LAB_0065768d;
      }
      FUN_0064b9e0(0x80,(int)piVar11 + 0x162);
      FUN_0065bf00((int)piVar11 + 0x172,0x10);
      FUN_00656aa0();
    }
  }
  uVar7 = FUN_0046d790();
  *(undefined1 *)(piVar11 + 0x66) = uVar7;
  FUN_0064b9e0(0x20,&local_50c);
  if (local_4f4 != 0) {
    FUN_006576b0(param_1,local_4f4);
  }
  *(undefined8 *)(piVar11 + 0x40) = *(undefined8 *)param_2;
  *(undefined8 *)(piVar11 + 0x42) = *(undefined8 *)(param_2 + 4);
  piVar11[0x44] = *(int *)(param_2 + 8);
  piVar11[0x28] = (int)local_50c;
  piVar11[0x24] = (int)local_50c;
  piVar11[0x2a] = (int)local_50c;
  if (*(char *)((int)piVar11 + 0x131) != '\0') {
    iVar9 = FUN_009c8e50(0x274);
    if (iVar9 != 0) {
      FUN_0065a500(iVar9,(int)piVar11 + 0x172);
    }
    FUN_00653fa0();
  }
  local_504 = 0;
  cVar6 = (**(code **)(*piVar11 + 0x24))(param_3,&local_504);
  if (cVar6 == '\0') {
    FUN_00656600(param_1,param_2);
    FUN_006550d0();
  }
  else {
    FUN_00655420(piVar11);
    FUN_006550d0();
    pcVar5 = *(code **)(*piVar11 + 0x14);
    piVar11[0x6d] = 7;
    (*pcVar5)();
    FUN_00656440(param_1);
  }
LAB_0065768d:
  FUN_00656aa0();
  return;
}