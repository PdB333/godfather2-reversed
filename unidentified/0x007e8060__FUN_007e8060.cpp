// FUNC_NAME: SomeClass::removeStringByHash
void __thiscall SomeClass::removeStringByHash(char *str)
{
  char cVar1;
  bool bFound;
  char *pcVar3;
  int hash;
  int index;
  HashEntry *entry;

  if (str != (char *)0x0) {
    // Compute hash of the string (note: length calculation seems to skip first character)
    pcVar3 = str;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    hash = computeStringHash(0x62dbe036, str, (int)pcVar3 - (int)(str + 1));
    index = 0;
    bFound = false;
    entry = &(this->registeredHashes[0]); // +0x57c: array of 20 HashEntry (each 24 bytes)
    do {
      if (bFound) {
        return;
      }
      if (entry->hash == hash) {
        bFound = true;
        entry->hash = 0;
      }
      index = index + 1;
      entry = entry + 1; // Actually step by 6 ints: +24 bytes (0x18)
      // Note: The original assembly shows piVar5 = piVar5 + 6 (int*), so each entry is 24 bytes.
    } while (index < 20);
  }
  return;
}