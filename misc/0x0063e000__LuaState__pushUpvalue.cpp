// FUNC_NAME: LuaState::pushUpvalue
uint LuaState::pushUpvalue(int *param_1, undefined4 param_2, int *param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  code *pcVar4;
  uint uVar5;
  undefined4 uVar6;
  int *piVar7;
  int iVar8;
  undefined8 uVar9;
  
  iVar2 = *param_1;
  uVar5 = 0;
  if (*(byte *)(iVar2 + 0x44) != 0) {
    piVar7 = param_1 + 0xf;
    do {
      if ((piVar7[-1] == *param_3) && (*piVar7 == param_3[1])) {
        return uVar5;
      }
      uVar5 = uVar5 + 1;
      piVar7 = piVar7 + 5;
    } while ((int)uVar5 < (int)(uint)*(byte *)(iVar2 + 0x44));
  }
  uVar5 = *(byte *)(iVar2 + 0x44) + 1;
  piVar7 = param_3;
  if (0x20 < uVar5) {
    uVar6 = FUN_00636c00("too many %s (limit=%d)","upvalues",0x20);
    uVar9 = FUN_00638b80(uVar6);
    piVar7 = (int *)((ulonglong)uVar9 >> 0x20);
    uVar5 = (uint)uVar9;
  }
  if (*(int *)(iVar2 + 0x24) < (int)uVar5) {
    iVar3 = *(int *)(iVar2 + 0x24);
    iVar8 = iVar3 * 2;
    if (iVar8 < 4) {
      iVar8 = 4;
    }
    else if (0x3ffffffd < iVar3) {
      if (0x7ffffff8 < iVar3) {
        FUN_00633920(param_1[4],&DAT_00e2f044);
        pcVar4 = (code *)swi(3);
        uVar5 = (*pcVar4)();
        return uVar5;
      }
      iVar8 = 0x7ffffffd;
    }
    uVar6 = FUN_006279a0(iVar3 * 4,iVar8 * 4);
    *(int *)(iVar2 + 0x24) = iVar8;
    *(undefined4 *)(*param_1 + 0x1c) = uVar6;
    piVar7 = param_3;
  }
  *(undefined4 *)(*(int *)(*param_1 + 0x1c) + (uint)*(byte *)(iVar2 + 0x44) * 4) = param_2;
  uVar5 = (uint)*(byte *)(iVar2 + 0x44);
  *(undefined8 *)(param_1 + uVar5 * 5 + 0xe) = *(undefined8 *)piVar7;
  *(undefined8 *)(param_1 + uVar5 * 5 + 0x10) = *(undefined8 *)(piVar7 + 2);
  param_1[uVar5 * 5 + 0x12] = piVar7[4];
  bVar1 = *(byte *)(iVar2 + 0x44);
  *(byte *)(iVar2 + 0x44) = bVar1 + 1;
  return (uint)bVar1;
}