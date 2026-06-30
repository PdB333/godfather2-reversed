// FUNC_NAME: PtrArray::reserve
void __thiscall PtrArray::reserve(int newCapacity)
{
  int *newArray;
  int *oldArray;
  int *newSlot;
  int *oldSlot;
  uint i;
  
  if (this->m_nCapacity < newCapacity) {
    newArray = (int *)allocMemory(newCapacity * 4);  // +0x94: allocNew
    if (this->m_pData != 0) {
      i = 0;
      newSlot = newArray;
      if (this->m_nCount != 0) {
        do {
          oldSlot = (int *)(this->m_pData + i * 4);
          if (newSlot == (int *)0x0) {
            if (*oldSlot != 0) {
              // If new slot is null, clear back-pointer (shouldn't happen)
              *(undefined4 *)(*oldSlot + 8) = 0;  // +0x08: back pointer
              goto LAB_cleanOld;
            }
          }
          else {
            *newSlot = 0;
            *newSlot = *oldSlot;
            if (*oldSlot != 0) {
              // Update object's back-pointer to new slot
              *(int **)(*oldSlot + 8) = newSlot;  // +0x08: back pointer
LAB_cleanOld:
              // Clear old pointer to avoid dangling ref
              *oldSlot = 0;
            }
          }
          i = i + 1;
          newSlot = newSlot + 1;
        } while (i < (uint)this->m_nCount);
      }
      freeMemory(this->m_pData);  // +0x94: freeOld
    }
    this->m_pData = newArray;
    this->m_nCapacity = newCapacity;
  }
  return;
}