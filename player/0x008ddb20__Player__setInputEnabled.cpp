// FUNC_NAME: Player::setInputEnabled
void __thiscall Player::setInputEnabled(int thisPtr, char enabled)
{
  if (enabled == '\0') {
    // Disable input: set bit 2 (0x04) in flags at +0x30
    *(byte *)(thisPtr + 0x30) = *(byte *)(thisPtr + 0x30) | 4;
    // Check if global pointer at DAT_012233a0+4 is valid and not a specific value (0x1f30)
    if ((**(int **)(DAT_012233a0 + 4) != 0) && (**(int **)(DAT_012233a0 + 4) != 0x1f30)) {
      // Call some function to disable input (e.g., clear controller state)
      FUN_0079d680(0);
    }
    // Clear bit 1 (0x02) in flags at +0x30
    *(byte *)(thisPtr + 0x30) = *(byte *)(thisPtr + 0x30) & 0xfd;
    return;
  }
  // Enable input: clear bit 2 (0x04) in flags at +0x30
  *(byte *)(thisPtr + 0x30) = *(byte *)(thisPtr + 0x30) & 0xfb;
  return;
}