// FUNC_NAME: SomeClass::ensureInitialized
void __fastcall SomeClass::ensureInitialized(int thisPtr)
{
  // Check if bit 6 of field at +0x4c is not set
  if ((*(uint *)(thisPtr + 0x4c) >> 6 & 1) == 0) {
    // Call initialization function
    FUN_00440c20();
    // Set bit 6 of field at +0x4c to mark as initialized
    *(uint *)(thisPtr + 0x4c) = *(uint *)(thisPtr + 0x4c) | 0x40;
  }
}