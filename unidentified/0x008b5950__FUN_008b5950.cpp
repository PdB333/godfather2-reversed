// FUNC_NAME: SomeClass::updateTick
void __fastcall SomeClass::updateTick(int thisPtr)
{
  // Check bit 0 of flags at +0x188
  if ((*(byte *)(thisPtr + 0x188) & 1) != 0) {
    FUN_008b3c40(); // likely updateSomeSubsystemA
  }
  // Check bit 1 of flags at +0x188
  if ((*(uint *)(thisPtr + 0x188) >> 1 & 1) != 0) {
    FUN_008b4d40(); // likely updateSomeSubsystemB
  }
  // Always called
  FUN_008ac450(); // likely baseUpdateTick
  return;
}