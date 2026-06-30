// FUNC_NAME: AudioManager::setVolumeForCategory
void __thiscall AudioManager::setVolumeForCategory(int *categoryList, byte categoryIndex, float volume)
{
  int categoryPtr;
  float scaledVolume;
  byte categoryCount;
  int in_EAX;
  uint loopCount;
  int roundedVolume;
  
  // Check if audio system is initialized (in_EAX likely points to AudioManager instance)
  if ((in_EAX != 0) && 
      (categoryCount = ((*(byte *)(*(int *)(in_EAX + 8) + 8) & 1) != 0) + 1, categoryCount != 0)) {
    loopCount = (uint)categoryCount;
    do {
      categoryPtr = *categoryList;
      if (categoryPtr != 0) {
        // Set flags: 0x120 = category volume dirty flag? (bit 5 and 6)
        *(ushort *)(categoryPtr + 0x10) = *(ushort *)(categoryPtr + 0x10) | 0x120;
        
        // Scale volume by global multiplier (DAT_00e445e0)
        scaledVolume = volume * DAT_00e445e0;
        
        // Store category index and sub-index (0 = master?)
        *(byte *)(categoryPtr + 0x1c) = categoryIndex;  // +0x1c: categoryIndex
        *(byte *)(categoryPtr + 0x1d) = 0;               // +0x1d: subCategoryIndex
        
        // Store unaff_EDI (likely some audio handle or context)
        *(int *)(categoryPtr + 0x20) = unaff_EDI;        // +0x20: audioContext
        
        // Round and store volume as integer (scaled)
        roundedVolume = (int)(scaledVolume + 0.5f);      // ROUND macro
        *(int *)(categoryPtr + 0x14) = roundedVolume;    // +0x14: volume
        
        // Apply volume change to audio system
        FUN_005dbc10(*(ushort *)(categoryPtr + 8),       // +0x08: audioHandle
                     categoryIndex,
                     roundedVolume,
                     ~(byte)*(ushort *)(categoryPtr + 0x10) & 1);  // invert flag bit 0
      }
      categoryList = categoryList + 1;
      loopCount = loopCount - 1;
    } while (loopCount != 0);
  }
  return;
}