// FUNC_NAME: HashTable::findIndex
uint __thiscall HashTable::findIndex(void* pEntry, int nBaseIndex)
{
  // this: HashTable*
  // +0x04: pointer to TableInfo structure (buffer + count)
  // +0x1c: sentinel value used for "empty" entries
  TableInfo* pTableInfo = *(TableInfo**)((uint8*)this + 4);
  uint uCount = *((uint*)pTableInfo + 1);   // offset 4 from TableInfo
  // +0x00 of pEntry: hash key stored as a signed char at offset 0x10
  uint uKey = (uint)((uint8*)pEntry + *(int8*)((uint8*)pEntry + 0x10));
  uint uSentinel = *(uint*)((uint8*)this + 0x1c);
  
  if (uKey == uSentinel)
  {
    // Return index beyond the current count (for insertion)
    return nBaseIndex + uCount;
  }
  
  // The actual entry array starts at offset 0x40 from the buffer
  int* pCurrentKey = (int*)((uint8*)pTableInfo->pBuffer + 0x40);
  
  for (uint i = 0; i < uCount; i++)
  {
    if (*pCurrentKey == (int)uKey)
    {
      return i;
    }
    pCurrentKey = (int*)((uint8*)pCurrentKey + 0x1c); // each entry is 28 bytes
  }
  
  return 0xFFFFFFFF; // not found
}