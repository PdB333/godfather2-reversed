// Xbox PDB: AptCharacterInst::sMethod_unloadMovie
// FUNC_NAME: AptCharacter::processCharacterUpdate
undefined4 FUN_005b6850(undefined4 param_1, int param_2)

{
  int *piVar1;
  code *pcVar2;
  uint uVar3;
  undefined4 uVar4;
  uint *puVar5;
  uint *puVar6;
  int unaff_FS_OFFSET;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  int local_8;
  undefined1 *local_4;
  
  if (param_2 == 0) goto LAB_005b68e5;
  local_14 = "nParams == 0";
  local_10 = "..\\source\\Apt\\AptCharacter.cpp";
  local_c = 0x59f;
  local_8 = 2;
  local_4 = &DAT_01129132;
  if (DAT_01129132 == '\0') goto LAB_005b68e5;
  piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
  uVar3 = 1;
  if (piVar1 == (int *)0x0) {
LAB_005b68c3:
    if ((uVar3 & 2) != 0) {
      *local_4 = 0;
    }
  }
  else {
    uVar3 = (**(code **)(*piVar1 + 8))(&local_14,"nParams == 0");
    if (local_4 != (undefined1 *)0x0) goto LAB_005b68c3;
  }
  if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
     (((uVar3 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
    pcVar2 = (code *)swi(3);
    uVar4 = (*pcVar2)();
    return uVar4;
  }
LAB_005b68e5:
  puVar5 = (uint *)FUN_0059c3b0();
  FUN_005a19c0();
  if ((~(byte)(*puVar5 >> 0xf) & 1) == 0) {
    if (puVar5[0x15] != 0) {
      uVar4 = FUN_005bc1e0();
      if (puVar5[0xd] != 0) {
        puVar6 = (uint *)FUN_005bb150(uVar4);
        if (puVar6 == puVar5) {
          FUN_005bad80(uVar4);
        }
      }
    }
    FUN_005aa310();
  }
  return DAT_0119cbbc;
}