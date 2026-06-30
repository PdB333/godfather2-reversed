// FUNC_NAME: Entity::updateTimer
void __thiscall Entity::updateTimer(int this, float deltaTime)
{
  // deltaTime is the frame's elapsed time
  // Calls a helper to integrate time (likely a timer accumulator)
  FUN_006b5c50(deltaTime);

  // +0x74: frame tick counter, incremented each update
  *(int *)(this + 0x74) = *(int *)(this + 0x74) + 1;

  // +0x80: a float threshold (e.g., cooldown or expiration time)
  // _DAT_00d577a0: likely a global constant or game time
  // +0x34: flags field, bit 29 (0x20000000) indicates a pause/disable flag
  if ((*(float *)(this + 0x80) <= _DAT_00d577a0) &&
     ((*(uint *)(this + 0x34) >> 0x1d & 1) == 0))
  {
    FUN_006b59f0(); // timer expired and not paused -> fire event or transition
    return;
  }
  FUN_006b2f70(); // normal update path
  return;
}