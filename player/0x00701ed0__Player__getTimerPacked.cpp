// FUNC_NAME: Player::getTimerPacked
unsigned int __thiscall Player::getTimerPacked(int thisPtr)
{
  int timer;

  if (*(int *)(thisPtr + 0x2d0) != 0) {  // Check if timer is active
    timer = FUN_00700090(*(int *)(thisPtr + 0x334));  // Get base value from ID at +0x334
    timer += *(int *)(thisPtr + 0x328);               // Add offset/duration from +0x328
    // Return packed format: high 24 bits = timer >> 8, low 8 bits = 1 if timer != 0
    return (timer & 0xFFFFFF00) | (timer != 0 ? 1 : 0);
  }
  return 0;  // Timer not active, return 0
}