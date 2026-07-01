// FUNC_NAME: SomeClass::clearDamageFlag

void __fastcall SomeClass::clearDamageFlag(int *thisPtr)
{
  float10 fVar1;
  
  // Check bit 6 of field at offset 0x970 (0x25c * 4)
  if (((uint)thisPtr[0x25c] >> 6 & 1) != 0) {
    // Call virtual function at vtable+0xC0 (likely getDamageTimer or similar)
    fVar1 = (float10)(**(code **)(*thisPtr + 0xc0))();
    if ((float10)0 < fVar1) {
      // Clear bit 6 of the flag field
      thisPtr[0x25c] = thisPtr[0x25c] & 0xffffffbf;
      // Call some cleanup function
      FUN_007f7050();
      return;
    }
  }
  return;
}