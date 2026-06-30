// FUNC_NAME: SomeClass::addEntry
undefined4 __thiscall addEntry(int this, undefined4 *entryData)
{
  int currentCount;
  undefined4 *dest;
  
  // Check if we've reached the maximum capacity (7 entries)
  // +0x650 stores the current count of entries
  if (7 < *(int *)(this + 0x650)) {
    return 0;
  }
  
  // Calculate destination pointer: base + 0x50 + (currentCount * 0xC0)
  // Each entry is 0xC0 (192) bytes, starting at offset 0x50 from this
  dest = (undefined4 *)(*(int *)(this + 0x650) * 0xc0 + 0x50 + this);
  
  // Copy 0x30 dwords (0xC0 bytes) from source to destination
  for (int i = 0x30; i != 0; i = i + -1) {
    *dest = *entryData;
    entryData = entryData + 1;
    dest = dest + 1;
  }
  
  // Increment the entry count
  *(int *)(this + 0x650) = *(int *)(this + 0x650) + 1;
  
  return 1;
}