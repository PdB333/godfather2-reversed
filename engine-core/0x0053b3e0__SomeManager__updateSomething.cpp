// FUNC_NAME: SomeManager::updateSomething
void SomeManager::updateSomething(void)
{
  // Check if the object at the computed index in the global array is non-null
  // DAT_01125389 is likely a current index or type selector
  // DAT_011254a8 is the base of an array of 0x3c-byte structures
  if (*(int *)(&DAT_011254a8 + (uint)DAT_01125389 * 0x3c) != 0) {
    // Call the update function on that object
    FUN_006063b0();
  }
  return;
}