// FUNC_NAME: PatternCapture::setCaptureValue
void __fastcall PatternCapture::setCaptureValue(int this)
{
  int *piVar1;
  int iVar2;
  int extraout_ECX;
  int iVar3;
  int unaff_EDI;
  
  iVar3 = *(int *)(unaff_EDI + 0xc) + -1; // +0x0C = captureCount
  if (-1 < iVar3) {
    piVar1 = (int *)(unaff_EDI + 0x14 + iVar3 * 8); // +0x14 = captureArray start (each entry: 8 bytes)
    do {
      if (*piVar1 == -1) goto LAB_0062bc4c; // Check if capture slot is unused
      iVar3 = iVar3 + -1;
      piVar1 = piVar1 + -2;
    } while (-1 < iVar3);
  }
  FUN_00627bd0("invalid pattern capture"); // Error: no free capture slot found
  param_1 = extraout_ECX;
LAB_0062bc4c:
  *(int *)(unaff_EDI + 0x14 + iVar3 * 8) = param_1 - *(int *)(unaff_EDI + 0x10 + iVar3 * 8); // Store offset from pattern start
  iVar2 = FUN_0062bd60(); // Validate capture
  if (iVar2 == 0) {
    *(undefined4 *)(unaff_EDI + 0x14 + iVar3 * 8) = 0xffffffff; // Mark as invalid
  }
  return;
}