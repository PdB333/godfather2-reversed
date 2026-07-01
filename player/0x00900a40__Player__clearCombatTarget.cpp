// FUNC_NAME: Player::clearCombatTarget
void __fastcall Player::clearCombatTarget(int thisPtr)
{
  // Check if the combat target flag (bit 15 at offset 0x180) is set
  if ((*(ushort *)(thisPtr + 0x180) & 0x8000) != 0) {
    // Clear the combat target state
    FUN_009008a0();
    // Release the combat target reference (DAT_012069d4 is likely a global combat target pointer)
    FUN_004086d0(&DAT_012069d4);
    // Clear the flag bit
    *(ushort *)(thisPtr + 0x180) = *(ushort *)(thisPtr + 0x180) & 0x7fff;
  }
  return;
}