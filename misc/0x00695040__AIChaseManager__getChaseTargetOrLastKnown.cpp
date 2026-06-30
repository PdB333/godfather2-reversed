// FUNC_NAME: AIChaseManager::getChaseTargetOrLastKnown
void __thiscall getChaseTargetOrLastKnown(int thisPtr, int *outTargetInfo, undefined4 targetID)
{
  int targetIndex;
  int *piVar2;
  int chaseInfo;
  int lastKnownPos;
  int currentTarget;
  undefined4 lastKnownID;
  
  targetIndex = FUN_00694950(targetID);
  chaseInfo = targetIndex;
  if (thisPtr == 0) {
    FUN_00b97aea(); // likely assertion/error handler
  }
  currentTarget = thisPtr;
  if (targetIndex != *(int *)(thisPtr + 4)) { // compare with current target index
    targetIndex = FUN_004d4b20(targetIndex + 0xc); // check if has valid last known pos
    if (-1 < targetIndex) {
      piVar2 = &currentTarget;
      goto LAB_0069508e;
    }
  }
  lastKnownID = *(undefined4 *)(thisPtr + 4); // fallback: use last known position
  lastKnownPos = thisPtr;
  piVar2 = &lastKnownPos;
LAB_0069508e:
  targetIndex = piVar2[1]; // copy target info struct
  *outTargetInfo = *piVar2;
  outTargetInfo[1] = targetIndex;
  return;
}