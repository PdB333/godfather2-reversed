// FUNC_NAME: RelocatableHashTable::fixupAndHash

void RelocatableHashTable::fixupAndHash(void)
{
  // this is unaff_EDI, an int* passed in edi (__thiscall)
  // Structure layout:
  // +0x00: int* pFirstString
  // +0x04: int flags (low byte used as hashType)
  // +0x06: short entryCount
  // +0x08: int* pHashArray    (output array)
  // +0x0C: int* pEntries      (array of Entry, size 0x18 each)

  int *thisPtr = this; // unaff_EDI

  // Relocate the three main pointers by adding 'this'
  *thisPtr += (int)thisPtr;                           // +0x00: first string offset -> absolute
  thisPtr[2] += (int)thisPtr;                         // +0x08: hash array
  thisPtr[3] += (int)thisPtr;                         // +0x0C: entries array

  int entryIndex = 0;
  short count = *(short *)((int)thisPtr + 6);          // entryCount at +0x06

  if (count != 0)
  {
    int entryOffset = 0; // offset into entries array in bytes
    do
    {
      Entry *entry = (Entry *)(thisPtr[3] + entryOffset); // each entry is 0x18 bytes
      int subEntryIndex = 0;

      // Relocate entry's three pointers by adding 'this'
      entry->stringPtr += (int)thisPtr;        // +0x00: string pointer
      entry->field_10 += (int)thisPtr;         // +0x10: piVar9[4] -> sub-entry array base?
      entry->field_14 += (int)thisPtr;         // +0x14: piVar9[5] -> sub-entry data start?

      // Process sub-entries if subEntryCount != 0
      if (entry->subEntryCount != 0)
      {
        int subIndex = 0;
        do
        {
          // Each sub-entry is 5 bytes: flag (1) + offset (4)
          char *subEntryBase = (char *)entry->field_14 + subIndex * 5;
          if (*subEntryBase == '\0') // flag byte is 0 -> adjust the following 4-byte offset
          {
            int *offsetPtr = (int *)(subEntryBase + 1);
            *offsetPtr += (int)thisPtr; // relocate offset by adding 'this'
          }
          subEntryIndex++;
          subIndex++;
        } while (subEntryIndex < (int)(uint)entry->subEntryCount);
      }

      // Compute hash if the low byte of flags at +0x04 is < 3
      if (*(byte *)(thisPtr + 1) < 3) // note: this is the first byte of the int at +0x04
      {
        char *firstStr = (char *)*thisPtr; // first string pointer
        char *p = firstStr;
        while (*p != '\0') p++;
        int firstLen = (int)(p - (firstStr + 1)); // length excluding null? Actually calculates length-1? Let's compute: pcVar4 - (pcVar3 + 1) = (p - (firstStr+1)) = strlen - 1. But in hash usually includes full string. Might be intentional. We'll replicate.

        unsigned int hash = FUN_00ab8560(0, firstStr, firstLen);

        char *entryStr = (char *)entry->stringPtr;
        p = entryStr;
        while (*p != '\0') p++;
        int entryLen = (int)(p - (entryStr + 1));
        hash = FUN_00ab8560(hash, entryStr, entryLen);

        // Store hash in the output array (pHashArray)
        ((int *)thisPtr[2])[entryIndex] = hash;
      }

      entryOffset += 0x18; // move to next entry
      entryIndex++;
    } while (entryIndex < (int)(uint)count);
  }
}