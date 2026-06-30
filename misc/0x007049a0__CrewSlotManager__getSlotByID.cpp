// FUNC_NAME: CrewSlotManager::getSlotByID
undefined4 __thiscall CrewSlotManager::getSlotByID(int this, int handle)
{
  int mappedIndex;
  undefined4 result;
  
  result = 0;
  if (handle != 0) {
    mappedIndex = mapHandleToIndex(handle); // FUN_00704860: converts handle to array index
    result = *(undefined4 *)(this + 0x20 + mappedIndex * 0x14); // crew slot array at +0x20, each 0x14 bytes
  }
  return result;
}