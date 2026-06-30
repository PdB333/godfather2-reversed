// FUNC_NAME: ArrayManager::findAndRemoveByIndex
bool __thiscall ArrayManager::findAndRemoveByIndex(undefined4 this, undefined4 *param_2, int param_3)
{
  bool bFound;
  uint uIndex;
  int *piCurrent;
  
  bFound = false;
  uIndex = 0;
  if (param_2[1] != 0) {
    piCurrent = (int *)*param_2;
    while (*piCurrent != param_3) {
      uIndex = uIndex + 1;
      piCurrent = piCurrent + 1;
      if ((uint)param_2[1] <= uIndex) {
        return bFound;
      }
    }
    bFound = -1 < (int)uIndex;
    if (bFound) {
      // Call to remove function (likely marking the element as removed)
      FUN_00791350(this);
      // Call to shift remaining elements
      FUN_006be9f0(uIndex);
    }
  }
  return bFound;
}