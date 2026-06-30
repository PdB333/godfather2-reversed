// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
undefined4 * __thiscall GodfatherGameManager::GodfatherGameManager(undefined4 *this, void *initData)
{
  int i;
  undefined4 *fieldArray;
  int count;
  
  // +0x04: some flag (set to 1)
  this[1] = 1;
  // +0x08: counter (set to 0)
  this[2] = 0;
  // +0x0C: pointer to static data (likely a vtable or singleton manager)
  this[3] = &PTR_LAB_00d5c67c;
  // Set global singleton pointer to this instance
  DAT_011298e0 = this;
  // +0x10: stored init data pointer
  this[4] = initData;
  // Set vtable pointer
  *this = &PTR_FUN_00d5c684;
  // Update static pointer again (possibly a secondary vtable or alternative)
  this[3] = &PTR_LAB_00d5c680;

  // Initialize first array of 18 entries, each 9 dwords (36 bytes)
  fieldArray = this + 5;        // offset 0x14
  count = 18;
  do {
    fieldArray[0] = 0;          // +0x00
    fieldArray[5] = 0;          // +0x14 (offset 5 dwords)
    fieldArray[6] = 0;          // +0x18
    fieldArray[7] = 0;          // +0x1C
    *(byte *)(fieldArray + 8) = 0; // +0x20 (byte)
    fieldArray += 9;            // advance 36 bytes
    count--;
  } while (count >= 0);

  // Initialize second array of 48 entries, each 9 dwords (36 bytes)
  fieldArray = this + 0xA7;     // offset 0x29C (167 dwords)
  count = 48;
  do {
    fieldArray[0] = 0;
    fieldArray[5] = 0;
    fieldArray[6] = 0;
    fieldArray[7] = 0;
    *(byte *)(fieldArray + 8) = 0;
    fieldArray += 9;
    count--;
  } while (count >= 0);

  // Initialize third array of 93 entries, each 9 dwords (36 bytes)
  fieldArray = this + 599;      // offset 0x95C (599 dwords)
  count = 93;
  do {
    fieldArray[0] = 0;
    fieldArray[5] = 0;
    fieldArray[6] = 0;
    fieldArray[7] = 0;
    *(byte *)(fieldArray + 8) = 0;
    fieldArray += 9;
    count--;
  } while (count >= 0);

  // If init data pointer is valid, call a virtual function at offset 8 from it
  if (initData != (void *)0x0) {
    (**(code **)(*(int *)initData + 8))();
  }

  // Copy initial data from global buffer if its first word is non-zero
  // FUN_00408900 is likely memcpy/memmove
  if (DAT_012069c4 != 0) {
    memcpy(this, &DAT_012069c4, 0x8000);
  }

  return this;
}