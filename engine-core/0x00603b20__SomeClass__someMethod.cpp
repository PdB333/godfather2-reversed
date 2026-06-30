// FUNC_NAME: SomeClass::someMethod
void SomeClass::someMethod(void)
{
  // Check if bit 2 of the flags at offset 0x4c is not set
  if ((*(uint *)(this + 0x4c) >> 2 & 1) == 0) {
    // Call the helper function twice
    FUN_00603c50(this);
    FUN_00603c50(this);
    // Set bit 2 of the flags at offset 0x4c
    *(uint *)(this + 0x4c) = *(uint *)(this + 0x4c) | 4;
  }
  return;
}