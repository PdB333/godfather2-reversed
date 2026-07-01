// FUNC_NAME: EntityDataManager::getAttackTargetById
undefined4 __thiscall EntityDataManager::getAttackTargetById(int thisPtr, int targetId)
{
  int targetIndex;
  int entityPtr;
  
  if (targetId != 0) {
    targetIndex = EntityDataManager::getIndexById(targetId);  // 0x00849a70 - lookup helper
    if ((-1 < targetIndex) && ((entityPtr = *(int *)(*(int *)(thisPtr + 0x10) + targetIndex * 4), entityPtr != 0))) {
      return *(undefined4 *)(entityPtr + 0x54);  // +0x54 - attackTarget field
    }
  }
  return 0;
}