// FUNC_NAME: AptManager::shutdownOrCheckInit
void FUN_005a0890(void)

{
  int *piVar1;
  code *pcVar2;
  uint uVar3;
  int unaff_FS_OFFSET;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  int local_8;
  undefined1 *local_4;
  
  // Check if Apt system is already initialized (static global flag)
  if (DAT_012055b0 != 0) goto LAB_005a0925;
  
  // Assertion data: "bAptIsInitialized" in file "../source/Apt/Apt.cpp" line 1071 (0x42f)
  local_14 = "bAptIsInitialized";
  local_10 = "..\\source\\Apt\\Apt.cpp";
  local_c = 0x42f;
  local_8 = 2;
  local_4 = &DAT_01128f5f;
  
  // Check if debug assertion is enabled
  if (DAT_01128f5f == '\0') goto LAB_005a0925;
  
  piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
  uVar3 = 1;
  if (piVar1 == (int *)0x0) {
LAB_005a0902:
    if ((uVar3 & 2) != 0) {
      *local_4 = 0;
    }
  }
  else {
    uVar3 = (**(code **)(*piVar1 + 8))(&local_14,"bAptIsInitialized");
    if (local_4 != (undefined1 *)0x0) goto LAB_005a0902;
  }
  
  // Debug assertion failure handler (likely triggers breakpoint)
  if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
     (((uVar3 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  
LAB_005a0925:
  // If Apt system is not shut down yet and there is an active AptEngine instance
  if ((DAT_0119cad0 == 0) && (DAT_0119a9cc != 0)) {
    // At offset +0x301c in the AptEngine, set some state/flag to 0
    *(undefined4 *)(DAT_0119a9cc + 0x301c) = 0;
  }
  return;
}