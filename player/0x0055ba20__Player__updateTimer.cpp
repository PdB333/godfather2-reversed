// FUNC_NAME: Player::updateTimer
void __fastcall Player::updateTimer(int *thisPtr)
{
  // +0x161: timer countdown byte
  if (*(char *)((int)thisPtr + 0x161) != '\0') {
    *(char *)((int)thisPtr + 0x161) = *(char *)((int)thisPtr + 0x161) - 1;
  }
  // +0x130 (0x4c * 4): some flag/state
  if ((*(char *)((int)thisPtr + 0x161) == '\0') && (thisPtr[0x4c] != 0)) {
    // vtable offset 300 (0x12c): callback when timer expires
    (**(code **)(*thisPtr + 300))();
  }
  FUN_0055bb70(); // likely update related timer/state
  return;
}