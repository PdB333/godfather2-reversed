// FUNC_NAME: Vehicle::getDistanceToTarget
float __thiscall Vehicle::getDistanceToTarget(int thisPtr, int targetId)
{
  int iVar1;
  int *piVar2;
  float distance;
  
  iVar1 = *(int *)(thisPtr + 0x11c) + -1;  // +0x11c: numTargets - 1 (last index)
  distance = DAT_00d5f6f0;  // Default large distance value (e.g., 999999.0f)
  
  if (-1 < iVar1) {
    piVar2 = (int *)(thisPtr + 0x5c + iVar1 * 0xc);  // +0x5c: targetArray (each entry 0xC bytes: targetId, ?, distance)
    while (*piVar2 != targetId) {
      iVar1 = iVar1 + -1;
      piVar2 = piVar2 + -3;  // Move to previous entry (0xC = 3 ints)
      if (iVar1 < 0) {
        return (float10)DAT_00d5f6f0;  // Target not found, return default
      }
    }
    if (_DAT_00d577a0 <= (float)piVar2[2]) {  // +0x08: distance value; compare against some threshold
      distance = DAT_01205228 - (float)piVar2[2];  // Calculate distance from some reference point
    }
  }
  return (float10)distance;
}