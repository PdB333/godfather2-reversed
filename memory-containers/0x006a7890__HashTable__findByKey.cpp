// FUNC_NAME: HashTable::findByKey
void __thiscall HashTable::findByKey(uint *this, uint *outEntry, uint *key)
{
  uint *currentEntry;
  uint *nextEntry;
  int slotIndex;
  uint *slotBase;
  
  slotBase = (uint *)*this;
  for (slotIndex = this[1]; slotIndex >= 0; slotIndex = slotIndex + -1) {
    currentEntry = *(uint **)(slotBase[2] + slotIndex * 4);
    if (currentEntry != (uint *)0x0) {
      do {
        nextEntry = currentEntry;
        if (*key <= *nextEntry) break;
        currentEntry = *(uint **)(nextEntry[2] + slotIndex * 4);
        slotBase = nextEntry;
      } while (currentEntry != (uint *)0x0);
    }
    currentEntry = *(uint **)slotBase[2];
    if (currentEntry == (uint *)0x0) break;
    if (*currentEntry == *key) {
      *outEntry = currentEntry;
      return;
    }
  }
  *outEntry = 0;
  return;
}