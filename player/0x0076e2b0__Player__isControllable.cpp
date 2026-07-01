// FUNC_NAME: Player::isControllable
bool __thiscall Player::isControllable(void *thisPtr)
{
  // thisPtr is likely a Player object
  // +0x50 : pointer to a large state structure (e.g., GameManager or SimManager)
  int *statePtr = *(int **)((char *)thisPtr + 0x50);

  // +0x1b94 : flags field within that state structure
  uint flags = *(uint *)((char *)statePtr + 0x1b94);

  // Check bit 4 (0x10): if set, player is disabled/uncontrollable
  if ((flags >> 4 & 1) != 0) {
    return false;
  }

  // Check bit 15 (0x8000): if set, check a special flag at +0x1b8c
  // If bit 15 is cleared, proceed; if set, require byte flag to be non-zero
  if ((flags >> 0xf & 1) != 0) {
    byte cutsceneOrDialogFlag = *(byte *)((char *)statePtr + 0x1b8c);
    if (cutsceneOrDialogFlag == 0) {
      return false;
    }
  }

  return true;
}