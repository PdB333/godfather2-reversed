// FUN_004acde0: CStringTable::assignValueToString
uint __thiscall CStringTable::assignValueToString(wchar_t *keyString, ushort newValue)
{
  bool found;
  uint idx;
  int entryOffset;
  wchar_t *entryStr;
  wchar_t *keyPtr;
  int cmpResult;
  bool less, greater;
  CStringTableEntry *entry;

  found = (this->entryCount != 0); // +0x08
  if (this->entryCount == 0) {
    return (uint)found;
  }
  entryOffset = 0;
  for (idx = 0; idx < this->entryCount; idx++) {
    entry = (CStringTableEntry *)(this->entryArray + entryOffset); // +0x04
    entryStr = entry->string;
    keyPtr = keyString;
    do {
      wchar_t c1 = *entryStr;
      wchar_t c2 = *keyPtr;
      if (c1 != c2) {
        less = (c1 < c2);
        greater = (c1 > c2);
        cmpResult = (1 - (uint)less) - (uint)(less != 0);
        break;
      }
      if (c1 == 0) {
        cmpResult = 0;
        break;
      }
      c1 = entryStr[1];
      c2 = keyPtr[1];
      if (c1 != c2) {
        less = (c1 < c2);
        greater = (c1 > c2);
        cmpResult = (1 - (uint)less) - (uint)(less != 0);
        break;
      }
      entryStr += 2;
      keyPtr += 2;
    } while (c1 != 0);
    if (cmpResult == 0) {
      entry->value = newValue; // +0x04
      found = true;
    }
    entryOffset += sizeof(CStringTableEntry); // 0x20
  }
  // Combine last index (truncated) with success flag
  return (idx >> 8) & 0xFFFFFF00 | (uint)found;
}