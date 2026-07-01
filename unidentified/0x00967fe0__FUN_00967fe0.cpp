// FUNC_NAME: SomeManager::cleanupOrSomething
void SomeManager::cleanupOrSomething(void)
{
  // Check if the global pointer (DAT_01223484) is non-null
  // and if the pointer at offset +0x0c from it is also non-null.
  if ((DAT_01223484 != 0) && (*(int *)(DAT_01223484 + 0xc) != 0)) {
    // Call a function (likely a destructor or cleanup) on the object
    // pointed to by PTR_LAB_00d79770, with a size parameter of 0xc.
    // This looks like a placement delete or a custom deallocation.
    FUN_008b5d40(&PTR_LAB_00d79770, 0xc);
  }
  return;
}