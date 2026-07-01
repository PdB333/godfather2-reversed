// FUNC_NAME: MemoryManager::allocateArray_28element

void MemoryManager::allocateArray_28element(uint count)
{
  undefined **local_8;
  undefined4 local_4;
  
  if (count == 0) {
    count = 0;
  }
  else if ((uint)(0xffffffff / (ulonglong)count) < 0x1c) {
    local_4 = 0;
    local_8 = &PTR_LAB_00e31050;
    if (DAT_0113d3a0 != (code *)0x0) {
      (*DAT_0113d3a0)(&local_8);
    }
    (*(code *)local_8[2])();
    std::_Throw((exception *)&local_8);
  }
  // Allocate count * 0x1C (28) bytes - array of 28-byte elements
  MemoryManager::allocate(count * 0x1C);
  return;
}