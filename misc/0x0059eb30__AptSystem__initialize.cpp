// FUNC_NAME: AptSystem::initialize
void AptSystem::initialize(int param_1)

{
  int *piVar1;
  code *pcVar2;
  uint uVar3;
  uint *puVar4;
  undefined4 uVar5;
  uint *puVar6;
  int unaff_FS_OFFSET;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  char *local_1c;
  char *local_18;
  int *local_14;
  int local_10;
  undefined1 *local_c;
  
  if (DAT_012055b0 != 0) goto LAB_0059ebc3;
  local_1c = "bAptIsInitialized";
  local_18 = "..\\source\\Apt\\Apt.cpp";
  local_14 = (int *)0x225;
  local_10 = 2;
  local_c = &DAT_01128f41;
  if (DAT_01128f41 == '\0') goto LAB_0059ebc3;
  piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
  uVar3 = 1;
  if (piVar1 == (int *)0x0) {
LAB_0059eba2:
    if ((uVar3 & 2) != 0) {
      *local_c = 0;
    }
  }
  else {
    uVar3 = (**(code **)(*piVar1 + 8))(&local_1c,"bAptIsInitialized");
    if (local_c != (undefined1 *)0x0) goto LAB_0059eba2;
  }
  if (((piVar1 != (int *)0x0) || (local_10 != 4)) &&
     (((uVar3 & 1) != 0 || ((local_10 == 0 || (local_10 == 1)))))) {
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
LAB_0059ebc3:
  puVar4 = (uint *)(*DAT_0119caf0)(0x24,0);
  puVar6 = (uint *)0x0;
  if (puVar4 != (uint *)0x0) {
    *puVar4 = *puVar4 & 0xffff8001 | 1;
    *(undefined2 *)((int)puVar4 + 2) = 0;
    *puVar4 = *puVar4 | 0x8000;
    FUN_005a0a80();
    puVar4[8] = 0xbeefceec;
    puVar6 = puVar4;
  }
  if (puVar6 != DAT_0119cbbc) {
    uVar3 = *puVar6 & 0x7fff;
    if ((uVar3 != 0x19) &&
       (((~(byte)(*puVar6 >> 0xf) & 1) != 0 ||
        (((uVar3 != 0xb && (uVar3 != 0x18)) && (uVar3 != 0x17)))))) {
      FUN_0059c230(puVar6);
    }
  }
  FUN_005a0980();
  FUN_005a1060();
  if ((local_14 != &local_10) && (local_14 != (int *)0x0)) {
    (*DAT_0119caf4)(local_14);
  }
  uVar9 = 1;
  uVar8 = 1;
  uVar7 = 0;
  puVar6[8] = 0xbeefceec;
  puVar4 = puVar6;
  uVar5 = FUN_0059e2f0(0,param_1,puVar6,1,1);
  FUN_005ad5b0(uVar5,uVar7,param_1,puVar4,uVar8,uVar9);
  (**(code **)(&DAT_0103aee0 + (*puVar6 & 0x7fff) * 4))(puVar6);
  return;
}