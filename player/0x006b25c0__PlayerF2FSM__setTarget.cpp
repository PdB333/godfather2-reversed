// FUNC_NAME: PlayerF2FSM::setTarget
void __thiscall PlayerF2FSM::setTarget(int thisPtr, int targetEntity)
{
  // +0xD8 likely stores the current target entity pointer
  if (*(int *)(thisPtr + 0xd8) != targetEntity)
  {
    *(int *)(thisPtr + 0xd8) = targetEntity;
    if (targetEntity != 0)
    {
      // +0x40 likely stores a class type ID or hash
      if (*(int *)(thisPtr + 0x40) == 0x637b907) // Could be a hash for "Player" or specific FSM state
      {
        // FUN_00898480 likely sets the target as a "friendly" or "non-hostile" (param 2 = 2)
        FUN_00898480(targetEntity, 2);
        return;
      }
      // FUN_008982e0 likely sets the target as "hostile" or "enemy" (param 2 = 2)
      FUN_008982e0(targetEntity, 2);
    }
  }
}