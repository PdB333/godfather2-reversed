// FUNC_NAME: SomeManager::clearOrResetList
void SomeManager::clearOrResetList(void)
{
  uint uVar1;
  
  if ((DAT_01129800 != 0) && (DAT_01129804 != 0)) {
    uVar1 = 0;
    if (DAT_01129804 != 0) {
      do {
        // Call release/free on each element in the list
        FUN_009c8f10(*(undefined4 *)(DAT_01129808 + uVar1 * 4));
        uVar1 = uVar1 + 1;
      } while (uVar1 < DAT_01129804);
    }
    // Release the list container itself
    FUN_009c8f10(DAT_01129808);
  }
  // Reset state: count, pointer, and flag
  DAT_01129804 = 0;  // count
  DAT_01129808 = 0;  // list pointer
  DAT_01129800 = 0;  // initialized flag
  return;
}