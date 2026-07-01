// FUNC_NAME: HashTable::resize
void __thiscall HashTable::resize(int *this, uint newCapacity)
{
  int *oldTable;
  int iVar2;
  int *newTable;
  uint idx;
  int *entry;
  
  if ((uint)this[2] < newCapacity) {
    newTable = (int *)FUN_009c8e80(newCapacity * 8);
    if (*this != 0) {
      idx = 0;
      entry = newTable;
      if (this[1] != 0) {
        do {
          oldTable = (int *)(*this + idx * 8);
          if (entry != (int *)0x0) {
            iVar2 = *oldTable;
            *entry = iVar2;
            entry[1] = 0;
            if (iVar2 != 0) {
              entry[1] = *(int *)(iVar2 + 4);
              *(int **)(iVar2 + 4) = entry;
            }
          }
          if (*oldTable != 0) {
            FUN_004daf90(oldTable);
          }
          idx = idx + 1;
          entry = entry + 2;
        } while (idx < (uint)this[1]);
      }
      FUN_009c8f10(*this);
    }
    *this = (int)newTable;
    this[2] = newCapacity;
  }
  return;
}