// FUNC_NAME: SomeClass::processBitfieldActions
void __fastcall processBitfieldActions(int thisPtr)
{
  // Check bit 8 (0x100) in the bitfield at +0x5C
  if ((*(uint *)(thisPtr + 0x5c) >> 8 & 1) != 0) {
    FUN_007907e0(0x975e53a5);
  }
  // Check bit 9 (0x200)
  if ((*(uint *)(thisPtr + 0x5c) >> 9 & 1) != 0) {
    FUN_007907e0(0x1e08e4b7);
  }
  // Check bit 10 (0x400)
  if ((*(uint *)(thisPtr + 0x5c) >> 10 & 1) != 0) {
    FUN_007907e0(0x9dc55bcc);
  }
  // Check bit 11 (0x800)
  if ((*(uint *)(thisPtr + 0x5c) >> 0xb & 1) != 0) {
    FUN_007907e0(0x8b836e49);
  }
  // Check bit 12 (0x1000)
  if ((*(uint *)(thisPtr + 0x5c) >> 0xc & 1) != 0) {
    FUN_007907e0(0xe3e6b859);
  }
  // Check bit 13 (0x2000)
  if ((*(uint *)(thisPtr + 0x5c) >> 0xd & 1) != 0) {
    FUN_007907e0(0x141ff8cc);
  }
  // Check bit 15 (0x8000) - special case with additional condition
  if ((*(uint *)(thisPtr + 0x5c) >> 0xf & 1) != 0) {
    // If value at +0x9C is non-zero, call and return early
    if (*(int *)(thisPtr + 0x9c) != 0) {
      FUN_007907e0(0x6fc0d0bc);
      return;
    }
    // Otherwise call the same function anyway
    FUN_007907e0(0x6fc0d0bc);
  }
  return;
}