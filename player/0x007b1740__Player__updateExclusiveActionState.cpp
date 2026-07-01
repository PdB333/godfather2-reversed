// FUNC_NAME: Player::updateExclusiveActionState
int __fastcall Player::updateExclusiveActionState(int this) // returns 0 if no change, 1 if state was set
{
  int *playerData; // eax, likely pointer to a larger player state struct
  char actionResult; // al from a virtual call
  int result; // 0 or 1

  playerData = *(int **)(this + 0x58); // +0x58: pointer to player data/handle
  result = 0;
  // Check if action index is non-zero and not equal to 0x48 (possibly an invalid or idle action)
  // Also check bit 29 of some large index (offset 0x927 * 4 = 0x249C) – likely a flags array or state machine
  if (((playerData[0x3fc] != 0) && (playerData[0x3fc] != 0x48)) && (((uint)playerData[0x927] >> 0x1d & 1) != 0))
  {
    // Call virtual function at vtable+0x270 (likely canPerformAction or getActionState)
    actionResult = (**(code (__thiscall **)(int))(*(int *)playerData + 0x270))();
    if (actionResult == 0) {
      // Action failed or cannot be performed – set state to 3 (e.g. ABORTED or FAILED)
      *(int *)(this + 0x74) = 3; // +0x74: action state / exclusive action state
    }
    else if (actionResult == '\x04') {
      // Action completed – set state to 2 (e.g. COMPLETED or DONE)
      *(int *)(this + 0x74) = 2; // +0x74: action state
      return 1; // indicate state was changed
    }
    result = 1; // indicate processing happened (even if unchanged)
  }
  return result;
}