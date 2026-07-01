// FUNC_NAME: PlayerSM::updateState
void __thiscall PlayerSM::updateState(int thisPtr, int *param_2)

{
  float fVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  undefined8 uStack_c;
  undefined4 uStack_4;
  
  if (((param_2 != (int *)0x0) && (iVar2 = FUN_00542d70(), iVar2 != 0)) &&
     (iVar2 = FUN_00542d70(), iVar2 != 0)) {
    iVar3 = FUN_0043b870(DAT_0113108c);
    if (((*(int *)(iVar3 + 0x48) == 0) || (*(int *)(iVar3 + 0x48) == 0x48)) &&
       (*(int *)(iVar2 + 0xc4) == 0)) {
      if ((*(char *)(thisPtr + 8) != '\0') &&
         ((iVar2 = FUN_006c12a0(param_2,0x10e5319e), iVar2 == 0 ||
          ((*(byte *)(iVar2 + 0xf28) & 1) == 0)))) {
        FUN_0087f870(0);
      }
    }
    else if ((*(char *)(thisPtr + 8) == '\0') && (((uint)param_2[0x322] >> 0xe & 1) == 0)) {
      *(undefined1 *)(thisPtr + 8) = 1;
    }
  }
  if (*(char *)(thisPtr + 8) == '\0') {
    if (*(char *)(thisPtr + 0x10) == '\0') goto LAB_00880dc2;
    uVar4 = (**(code **)(*param_2 + 0x58))();
    *(undefined4 *)(thisPtr + 0x134) = uVar4;
    fVar6 = (float10)FUN_00880140(param_2);
    *(undefined1 *)(thisPtr + 0x11) = *(undefined1 *)(thisPtr + 8);
    *(undefined4 *)(thisPtr + 0x2c) = 0;
    *(undefined4 *)(thisPtr + 0x30) = 0;
    iVar2 = FUN_00471610();
    *(undefined8 *)(thisPtr + 0x1c) = *(undefined8 *)(iVar2 + 0x30);
    uVar4 = *(undefined4 *)(iVar2 + 0x38);
    *(undefined4 *)(thisPtr + 0x28) = *(undefined4 *)(thisPtr + 0x134);
    *(undefined4 *)(thisPtr + 0x24) = uVar4;
    fVar7 = (float10)(**(code **)(*param_2 + 0x1a8))();
    *(float *)(thisPtr + 0x34) = (float)fVar7;
    *(float *)(thisPtr + 0x38) = (float)fVar6;
  }
  else {
    uVar4 = (**(code **)(*param_2 + 0x58))();
    *(undefined4 *)(thisPtr + 0x134) = uVar4;
    if (*(char *)(thisPtr + 0x10) != '\0') {
      fVar6 = (float10)(**(code **)(*param_2 + 0x1b0))();
      uVar5 = (int)*(char *)(param_2[0xd8] + 0xcd) + 1;
      fVar1 = DAT_00e541cc;
      if (uVar5 < 4) {
        fVar1 = *(float *)(&DAT_00e541c0 + uVar5 * 4);
      }
      fVar7 = (float10)FUN_0087fbb0(param_2);
      fVar8 = (float10)FUN_00880140(param_2);
      FUN_008806f0(param_2);
      *(float *)(thisPtr + 0x30) = (float)fVar7;
      *(undefined1 *)(thisPtr + 0x11) = *(undefined1 *)(thisPtr + 8);
      *(int *)(thisPtr + 0x2c) = (int)(fVar1 * (float)fVar6);
      iVar2 = FUN_00471610();
      uStack_c = *(undefined8 *)(iVar2 + 0x30);
      uStack_4 = *(undefined4 *)(iVar2 + 0x38);
      *(undefined8 *)(thisPtr + 0x1c) = *(undefined8 *)(iVar2 + 0x30);
      uVar4 = *(undefined4 *)(iVar2 + 0x38);
      *(undefined4 *)(thisPtr + 0x28) = *(undefined4 *)(thisPtr + 0x134);
      *(undefined4 *)(thisPtr + 0x24) = uVar4;
      fVar6 = (float10)(**(code **)(*param_2 + 0x1a8))();
      *(float *)(thisPtr + 0x34) = (float)fVar6;
      *(float *)(thisPtr + 0x38) = (float)fVar8;
      if (*(char *)(thisPtr + 0x208) != '\0') {
        FUN_0087ff70(param_2,&uStack_c);
      }
    }
    if (*(char *)(thisPtr + 0x209) != '\0') {
      FUN_008806f0(param_2);
      FUN_00880140(param_2);
      FUN_0087fb10(param_2);
      FUN_0087fc80(param_2);
    }
  }
  if (*(char *)(thisPtr + 0x10) != '\0') {
    FUN_008743f0();
  }
LAB_00880dc2:
  if (param_2 != (int *)0x0) {
    if (*(int *)(thisPtr + 0x1b8) != 0) {
      iVar2 = FUN_00471610();
      FUN_005e6580(*(undefined4 *)(thisPtr + 0x1b8),iVar2 + 0x30);
    }
    if ((*(char *)(thisPtr + 0x20a) != '\0') &&
       (iVar2 = (&DAT_0112e168)[*(int *)(thisPtr + 0x1c0) * 3], iVar2 != 0)) {
      iVar3 = FUN_00471610();
      FUN_005e6580(iVar2,iVar3 + 0x30);
    }
  }
  return;
}