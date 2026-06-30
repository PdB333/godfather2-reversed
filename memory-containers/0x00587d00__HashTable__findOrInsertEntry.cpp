// FUNC_NAME: HashTable::findOrInsertEntry
int * __thiscall HashTable::findOrInsertEntry(int *this, int hashTable, int key)
{
  int *bucketList;
  uint *bucketEntry;
  char *dataPtr;
  int foundValue1;
  int foundValue2;
  uint hashValue;
  
  dataPtr = *(char **)(key + 0x60);
  if (((dataPtr == (char *)0x0) || (*dataPtr != '\x02')) || (*(int **)(dataPtr + 4) == (int *)0x0)) {
    foundValue1 = -1;
  }
  else {
    foundValue1 = **(int **)(dataPtr + 4);
  }
  
  bucketList = *(int **)(*(int *)(hashTable + 0x70) + 0x30);
  hashValue = unaff_EDI % (uint)bucketList[1];
  bucketEntry = *(uint **)(*bucketList + hashValue * 4);
  
  do {
    if (bucketEntry == (uint *)0x0) {
LAB_00587d4b:
      dataPtr = (char *)0x0;
LAB_00587d4d:
      if (((dataPtr == (char *)0x0) || (*dataPtr != '\x02')) || (*(int **)(dataPtr + 4) == (int *)0x0)) {
        foundValue2 = -1;
      }
      else {
        foundValue2 = **(int **)(dataPtr + 4);
      }
      this[1] = key;           // +0x04: store key pointer
      this[2] = foundValue1;   // +0x08: store first extracted value
      this[4] = foundValue2;   // +0x10: store second extracted value
      *this = hashTable;       // +0x00: store hash table pointer
      this[3] = unaff_EDI;     // +0x0C: store hash value
      this[5] = 0;             // +0x14: initialize to zero
      return this;
    }
    if (*bucketEntry == unaff_EDI) {
      if ((bucketEntry != (uint *)0x0) && (bucketEntry != (uint *)0xfffffffc)) {
        dataPtr = (char *)bucketEntry[2];  // +0x08: data pointer from bucket entry
        goto LAB_00587d4d;
      }
      goto LAB_00587d4b;
    }
    bucketEntry = (uint *)bucketEntry[3];  // +0x0C: next bucket in chain
  } while( true );
}