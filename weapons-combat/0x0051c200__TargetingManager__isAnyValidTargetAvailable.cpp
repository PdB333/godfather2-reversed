// FUNC_NAME: TargetingManager::isAnyValidTargetAvailable
undefined TargetingManager::isAnyValidTargetAvailable() const
{
  int *pTargetListInfo; // result of getTargetListInfo()
  uint *pEntry; // pointer to current target entry
  byte bLocalFlags;
  int *pFilter; // interface pointer at +0x20
  int iFilterResult; // buffer for filter query
  int iNumTargets;
  int iCounter;
  uint uIndex;
  bool bResult;

  bResult = false;
  pTargetListInfo = (int *)GameManager::getTargetListInfo(); // FUN_004e9fa0
  iCounter = 0;
  int iBaseOffset = (*(int *)(*(int *)(__readfsdword(0x2c) + 0x2c) + 0x34) != 0) ? 0x98 : 0; // based on some global flag (e.g., difficulty)
  iNumTargets = *(int *)(pTargetListInfo + 1 + iBaseOffset); // count at offset iBaseOffset + 4 from info pointer
  if (iNumTargets < 1) {
    return 0;
  }

  do {
    pEntry = (uint *)((int)pTargetListInfo + iBaseOffset + iCounter * 0x10 + 0xc); // each entry is 0x10 bytes, starting at offset 0xc
    // Check global filter flag
    if (*(uint *)(*(int *)(this + 0x10) + 0x14) & 0x800) {
      pFilter = *(int **)(this + 0x20);
      if (pFilter != (int *)0x0) {
        pFilter[1]++; // ref count
      }
      iFilterResult = 0;
      int bQuery = (**(int (__thiscall **)(int *))(pFilter[0] + 8))(0x3eb08af9, &iFilterResult); // query filter with hash
      if (pFilter) {
        pFilter[1]--;
        if (pFilter[1] == 0) {
          (**(void (__thiscall **)(int *))(pFilter[0] + 4))(); // release
        }
      }
      if (bQuery != 0 && iFilterResult != 0) {
        // Check if target ID (second dword of entry) is in the filter's exclusion list
        uIndex = 0;
        int *pFilterData = (int *)iFilterResult;
        if (*(uint *)(pFilterData + 6) != 0) { // filterData->count at offset 0x18
          do {
            if (pFilterData[2 + uIndex] == pEntry[1]) { // compare with filter list entries (offset 0x8)
              if (uIndex != 0xffffffff) {
                goto LAB_SKIP_CHECK; // target excluded, skip to next conditions
              }
              break;
            }
            uIndex++;
          } while (uIndex < *(uint *)(pFilterData + 6));
        }
      }
    }

LAB_SKIP_CHECK:
    bLocalFlags = *(byte *)(*(int *)(this + 0x10) + 0x1d);
    if (((bLocalFlags == 0) || (*(uint *)(pEntry + 2) == 0)) ||
        ((*(byte *)(pEntry + 2) & bLocalFlags) != 0)) {
      if (TargetingManager::isTargetValid(*pEntry, 0) != 0) { // FUN_0051b5f0
        bResult = true;
      }
    }

    iCounter++;
    pTargetListInfo = (int *)GameManager::getTargetListInfo(); // refresh? but actually iVar6 is unchanged? The code recalculated iVar7 but not iVar6. In decompile, iVar6 is set once and reused. So we keep it.
    iBaseOffset = (*(int *)(*(int *)(__readfsdword(0x2c) + 0x2c) + 0x34) != 0) ? 0x98 : 0;
    iNumTargets = *(int *)(pTargetListInfo + 1 + iBaseOffset); // re-read count each iteration
  } while (iCounter < iNumTargets);

  return bResult;
}