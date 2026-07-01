// FUNC_NAME: SomeClass::getDistanceToTarget
float __thiscall getDistanceToTarget(int this, int target)
{
  int iVar1;
  int *piVar2;
  float result;
  
  iVar1 = *(int *)(this + 0x11c) + -1; // +0x11c: count of tracked targets
  result = DAT_00d5f6f0; // default large distance value (e.g., 999999.0f)
  
  if (-1 < iVar1) {
    piVar2 = (int *)(this + 0x5c + iVar1 * 0xc); // +0x5c: array of target entries (each 12 bytes)
    while (*piVar2 != target) {
      iVar1 = iVar1 + -1;
      piVar2 = piVar2 + -3; // move to previous entry (3 ints back)
      if (iVar1 < 0) {
        return (float)DAT_00d5f6f0;
      }
    }
    // Found target, check if distance is within some threshold
    if (_DAT_00d577a0 <= (float)piVar2[2]) { // piVar2[2] = distance to target
      result = DAT_01205228 - (float)piVar2[2]; // calculate remaining distance
    }
  }
  return (float)result;
}