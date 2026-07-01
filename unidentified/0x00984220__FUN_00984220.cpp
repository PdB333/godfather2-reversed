// FUNC_NAME: SomeClass::findEntryById
undefined1 __thiscall SomeClass::findEntryById(int this, int id, undefined4 *outEntry)
{
  uint index;
  undefined4 *entryPtr;
  undefined1 found;
  int local_24;
  code *local_18;
  
  found = 0;
  FUN_004d3b00(0); // likely a mutex lock or critical section enter
  index = 0;
  if (*(uint *)(this + 0xbc) != 0) { // +0xBC: count of entries
    entryPtr = *(undefined4 **)(this + 0xb8); // +0xB8: pointer to entry array
    do {
      if (entryPtr[9] == id) { // entry[9] is the ID field (offset 0x24 in entry)
        found = 1;
        *outEntry = *entryPtr; // copy first 4 bytes (likely a handle or pointer)
        FUN_004d3e20(entryPtr + 1); // copy function for entry data (offset 4)
        outEntry[5] = entryPtr[5]; // copy field at offset 0x14
        outEntry[6] = entryPtr[6]; // copy field at offset 0x18
        outEntry[7] = entryPtr[7]; // copy field at offset 0x1C
        *(undefined1 *)(outEntry + 8) = *(undefined1 *)(entryPtr + 8); // copy byte at offset 0x20
        *(undefined1 *)((int)outEntry + 0x21) = *(undefined1 *)((int)entryPtr + 0x21); // copy byte at offset 0x21
        outEntry[9] = entryPtr[9]; // copy ID field at offset 0x24
        break;
      }
      index = index + 1;
      entryPtr = entryPtr + 10; // each entry is 0x28 bytes (10 * 4)
    } while (index < *(uint *)(this + 0xbc));
  }
  if (local_24 != 0) {
    (*local_18)(local_24); // likely a cleanup or unlock call
  }
  return found;
}