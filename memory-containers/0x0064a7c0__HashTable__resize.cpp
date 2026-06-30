// FUNC_NAME: HashTable::resize

int HashTable::resize(int newCapacity)
{
  int *oldTable; // esi
  uint oldCount; // local variable
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  void *newTable;
  uint uVar5;
  uint uVar6;
  
  if (this->resizing == 0) {
    oldTable = this->table; // +0x00
    oldCount = this->count; // +0x04
    this->resizing = 1; // +0x08
    newTable = this->allocator(this->allocatorData, newCapacity * 4, this->allocatorParam); // +0x04, +0x14, +0x1C
    if (newTable != 0) {
      _memset(newTable, 0, newCapacity * 4);
      uVar6 = 0;
      this->count = newCapacity; // +0x04
      this->table = newTable; // +0x00
      if (oldCount != 0) {
        do {
          iVar4 = oldTable[uVar6];
          while (iVar4 != 0) {
            uVar5 = (*(uint *)(iVar4 + 8) >> 4) % this->count;
            iVar3 = *(int *)(iVar4 + 0x18); // next pointer
            *(undefined4 *)(iVar4 + 0x18) = *(undefined4 *)((int)newTable + uVar5 * 4);
            *(int *)((int)newTable + uVar5 * 4) = iVar4;
            iVar4 = iVar3;
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 < oldCount);
      }
      if (oldTable != 0) {
        this->deallocator(this->allocatorData, oldTable, oldCount * 4, this->allocatorParam); // +0x18, +0x04, +0x1C
      }
    }
    this->resizing = 0; // +0x08
  }
  return 1;
}