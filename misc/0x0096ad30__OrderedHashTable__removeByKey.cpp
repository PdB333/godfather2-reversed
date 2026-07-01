// FUNC_NAME: OrderedHashTable::removeByKey

void __thiscall OrderedHashTable::removeByKey(undefined4 *this, int *key)
{
  int iVar1;
  int iVar2;
  int bucketIndex;
  uint uVar1;
  int *bucketEntry;
  int *prevEntry;
  int *currentEntry;
  
  bucketIndex = this[1];
  prevEntry = (int *)*this;
  if (-1 < bucketIndex) {
    do {
      currentEntry = *(int **)(prevEntry[2] + bucketIndex * 4);
      if (currentEntry != (int *)0x0) {
        prevEntry = currentEntry;
        do {
          currentEntry = prevEntry;
          if (*key <= *prevEntry) break;
          currentEntry = *(int **)(prevEntry[2] + bucketIndex * 4);
          prevEntry = currentEntry;
        } while (currentEntry != (int *)0x0);
      }
      bucketIndex = bucketIndex + -1;
      *(int **)(this[5] + 4 + bucketIndex * 4) = prevEntry;
    } while (-1 < bucketIndex);
    if ((currentEntry != (int *)0x0) && (*currentEntry == *key)) {
      uVar1 = 0;
      do {
        iVar2 = *(int *)(*(int *)(this[5] + uVar1 * 4) + 8);
        iVar3 = uVar1 * 4;
        if (*(int **)(iVar2 + uVar1 * 4) != currentEntry) break;
        iVar1 = uVar1 * 4;
        uVar1 = uVar1 + 1;
        *(undefined4 *)(iVar2 + iVar3) = *(undefined4 *)(currentEntry[2] + iVar1);
      } while (uVar1 <= (uint)this[1]);
      FUN_009c8f10(currentEntry[2]);
      FUN_009c8eb0(currentEntry);
      this[4] = this[4] + -1;
    }
  }
  return;
}