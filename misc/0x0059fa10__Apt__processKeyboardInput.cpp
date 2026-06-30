// FUNC_NAME: Apt::processKeyboardInput
void Apt::processKeyboardInput(int param_1, int *param_2)
{
  int *piVar1;
  code *pcVar2;
  uint uVar3;
  uint *puVar5;
  int unaff_FS_OFFSET;
  undefined4 in_XMM0_Da;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  int local_8;
  undefined1 *local_4;
  
  if (DAT_012055b0 != 0) goto LAB_0059faa5;
  local_14 = "bAptIsInitialized";
  local_10 = "..\\source\\Apt\\Apt.cpp";
  local_c = 0x2c3;
  local_8 = 2;
  local_4 = &DAT_01128f52;
  if (DAT_01128f52 == '\0') goto LAB_0059faa5;
  piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
  uVar3 = 1;
  if (piVar1 == (int *)0x0) {
LAB_0059fa83:
    if ((uVar3 & 2) != 0) {
      *local_4 = 0;
    }
  }
  else {
    uVar3 = (**(code **)(*piVar1 + 8))(&local_14,"bAptIsInitialized");
    if (local_4 != (undefined1 *)0x0) goto LAB_0059fa83;
  }
  if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
     (((uVar3 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
LAB_0059faa5:
  uVar8 = 1;
  uVar7 = 1;
  uVar6 = 0;
  uVar4 = FUN_0059e2f0(0,param_1,1,1); // getAptDocument
  puVar5 = (uint *)FUN_005aea60(uVar4,uVar6,param_1,uVar7,uVar8); // findRootMovieClip
  if (puVar5 != DAT_0119cbbc) {
    uVar3 = *puVar5 & 0x7fff;
    if ((uVar3 != 0x19) && // not keyUp
       (((~(byte)(*puVar5 >> 0xf) & 1) != 0 ||
        (((uVar3 != 0xb && (uVar3 != 0x18)) && (uVar3 != 0x17)))))) {
      FUN_0059c230(puVar5); // dispatchKeyboardEvent
    }
  }
  FUN_005a9040(); // updateApt
  *param_2 = in_XMM0_Da;
  (**(code **)(&DAT_0103aee0 + (*puVar5 & 0x7fff) * 4))(puVar5);
  return;
}