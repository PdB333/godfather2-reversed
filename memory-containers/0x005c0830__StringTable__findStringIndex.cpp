// FUNC_NAME: StringTable::findStringIndex
// Address: 0x005c0830
// Class: StringTable (generic wide-string table)
// Method: int findStringIndex(const wchar_t* str) const
// Description: Searches an array of wide-string entries (each 24 bytes) for a matching string.
//   Returns the index (0-based) if found, or -1 if not found.
// Object layout:
//   +0x4: pointer to array of StringEntry (each 6 DWORDs = 24 bytes)
//   +0x8: count of entries (int)
// StringEntry layout:
//   +0x0: wchar_t* name (pointer to null-terminated wide string)

int __thiscall StringTable::findStringIndex(const wchar_t* str) const
{
  int index = 0;
  if (0 < this->count)
  {
    // Iterate over the array of StringEntry structures
    StringEntry* entryPtr = this->entries;
    do
    {
      const wchar_t* entryName = entryPtr->name;
      const wchar_t* searchStr = str;
      // Compare two wide characters at a time (16-bit comparison)
      do
      {
        wchar_t c1 = *entryName;
        wchar_t c2 = *searchStr;
        bool less = (c1 < c2);
        if (c1 != c2)
        {
          // Return -1 if c1 < c2, 1 if c1 > c2 (matches strcmp semantics)
          int cmp = (1 - (unsigned int)less) - (unsigned int)(less != 0);
          goto checkResult;
        }
        if (c1 == 0) break; // Both strings ended equally
        c1 = entryName[1];
        c2 = searchStr[1];
        less = (c1 < c2);
        if (c1 != c2)
        {
          int cmp = (1 - (unsigned int)less) - (unsigned int)(less != 0);
          goto checkResult;
        }
        entryName += 2;
        searchStr += 2;
      } while (c1 != 0);
      // Full match
      checkResult:
      if (cmp == 0)
      {
        return index;
      }
      index++;
      entryPtr = (StringEntry*)((unsigned int*)entryPtr + 6); // Advance by 6 DWORDs (24 bytes)
    } while (index < this->count);
  }
  return -1;
}