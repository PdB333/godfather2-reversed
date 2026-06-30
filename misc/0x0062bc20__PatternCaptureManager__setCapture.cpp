// FUNC_NAME: PatternCaptureManager::setCapture
void __fastcall PatternCaptureManager::setCapture(int param_1)
{
  int i;
  int *pSlot;

  i = *(int *)(this + 0x0c) + -1; // captureCount - 1
  if (i >= 0) {
    pSlot = (int *)(this + 0x14 + i * 8); // point to capture pair at index i
    do {
      if (*pSlot == -1) goto found; // slot is free
      i--;
      pSlot -= 2; // move to previous pair (8 bytes back)
    } while (i >= 0);
  }
  debugPrint("invalid pattern capture"); // FUN_00627bd0
  param_1 = ecx; // restore param_1 from saved ECX (compiler artifact)
found:
  // store the delta: param_1 - referenceValue
  *(int *)(this + 0x14 + i * 8) = param_1 - *(int *)(this + 0x10 + i * 8);
  if (validateCapture() == 0) { // FUN_0062bd60
    *(int *)(this + 0x14 + i * 8) = -1; // invalidate the capture
  }
}