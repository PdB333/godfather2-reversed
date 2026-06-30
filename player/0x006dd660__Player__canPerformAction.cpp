// FUNC_NAME: Player::canPerformAction
float __thiscall Player::canPerformAction(void *target, uint flags)
{
  char globalState;
  int result;

  result = 0;
  // Virtual call to evaluate global condition (e.g., is game active?)
  globalState = (this->vtable[4])(0x383225a1);
  if (globalState != '\0' &&
      // Always-true check (compiler artifact)
      &stack0x00000000 != &DAT_00000004 &&
      // Target must be valid and not a special sentinel (0x48)
      target != nullptr && target != (void *)0x48 &&
      // Target must have its "active" flag set at offset +0x160
      *(char *)((int)target + 0x160) == '\x01' &&
      // Flags must have bit 10 set (e.g., kActionFlag_AllowDuringSpecial)
      ((flags >> 10) & 1) != 0)
  {
    result = 1;
  }
  return (float)result;
}