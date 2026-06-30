// FUNC_NAME: EARS::Framework::someCollection::updateEntries
void __thiscall updateEntries(void* this)
{
  int* pEntryData;
  uint* puEntryFlags;
  int entryIndex;
  
  // Check if the entry has already been updated (flag at offset +0x04)
  if (*(char*)(this + 0x04) == '\0') {
    // Call entry initialization, passing the entry's base data pointer
    FUN_00535450(0, *(int*)this);
    // Mark the entry as updated
    *(char*)(this + 0x04) = 1;
  }
  
  // Allocate memory for 7 entries, each 8 dwords (32 bytes) wide
  // _MALLOC(sizeClass=5, alignment=7, flags=0, useArray=1, zero=0)
  pEntryData = (int*)FUN_0060cd00(5, 7, 0, 1, 0);
  if (pEntryData != (int*)0x0) {
    // Process 7 entries starting at offset +0xE0 from this object
    puEntryFlags = (uint*)(this + 0xE0);
    entryIndex = 7;
    do {
      // Get current entry flag value
      uint uEntryFlag = *puEntryFlags;
      
      // Call some system function that returns data via extraout_EDX
      FUN_00414aa0();
      
      // Read 4 dwords from the returned data at offsets +0x70, +0x74, +0x78, +0x7C
      uint uData0 = *(uint*)(extraout_EDX + 0x70);
      uint uData1 = *(uint*)(extraout_EDX + 0x74);
      uint uData2 = *(uint*)(extraout_EDX + 0x78);
      uint uData3 = *(uint*)(extraout_EDX + 0x7C);
      
      // Write entry data: first 3 dwords zero, then the flag and 4 data dwords
      // Structure: { 0, 0, 0, flag, data0, data1, data2, data3 } = 8 dwords total
      pEntryData[0] = 0;
      pEntryData[1] = 0;
      pEntryData[2] = 0;
      pEntryData[3] = uEntryFlag;
      pEntryData[4] = uData0;
      pEntryData[5] = uData1;
      pEntryData[6] = uData2;
      pEntryData[7] = uData3;
      
      pEntryData += 8;
      puEntryFlags += 1;
      entryIndex--;
    } while (entryIndex != 0);
    
    // Finalize the allocation and commit the entries
    FUN_0060cde0();
  }
  return;
}