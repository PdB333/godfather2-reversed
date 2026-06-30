// FUNC_NAME: AptManager::getAptResolution
void AptManager::getAptResolution(undefined4 *outWidth, undefined4 *outHeight)
{
  int *piVar1;
  code *pcVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  int unaff_FS_OFFSET;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  int local_8;
  undefined1 *local_4;
  
  if (DAT_012055b0 == 0) {
    local_14 = "bAptIsInitialized";
    local_10 = "..\\source\\Apt\\Apt.cpp";
    local_c = 0xbe;
    local_8 = 2;
    local_4 = &DAT_01128f3c;
    if (DAT_01128f3c != '\0') {
      piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
      uVar4 = 1;
      if (((piVar1 == (int *)0x0) ||
          (uVar4 = (**(code **)(*piVar1 + 8))(&local_14,"bAptIsInitialized"),
          local_4 != (undefined1 *)0x0)) && ((uVar4 & 2) != 0)) {
        *local_4 = 0;
      }
      if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
         (((uVar4 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
    }
  }
  if (DAT_0119a9cc != 0) {
    if ((*(int *)(**(int **)(DAT_0119a9cc + 0x2514) + 0x60) == 0) ||
       (cVar3 = FUN_0059ca10(), cVar3 == '\0')) {
      if (outWidth != (undefined4 *)0x0) {
        *outWidth = 0;
      }
      if (outHeight != (undefined4 *)0x0) {
        *outHeight = 0;
      }
    }
    else {
      iVar5 = FUN_0059c8b0();
      if (outWidth != (undefined4 *)0x0) {
        *outWidth = *(undefined4 *)(*(int *)(iVar5 + 8) + 0x1c);
      }
      if (outHeight != (undefined4 *)0x0) {
        *outHeight = *(undefined4 *)(*(int *)(iVar5 + 8) + 0x20);
        return;
      }
    }
  }
  return;
}