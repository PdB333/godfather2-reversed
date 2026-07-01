// FUNC_NAME: Player::updateSomething
void __fastcall Player::updateSomething(int thisPtr)
{
  // Check if byte at +0x162 is zero (some flag) and bit 2 of dword at +0xc88 is set
  if ((*(char *)(thisPtr + 0x162) == '\0') && ((*(uint *)(thisPtr + 0xc88) >> 2 & 1) != 0)) {
    // Call function at 0x0087f950 with argument 0 (likely a reset or clear function)
    FUN_0087f950(0);
  }
  // Call function at 0x004719e0 (likely a base class update or engine tick)
  FUN_004719e0();
}