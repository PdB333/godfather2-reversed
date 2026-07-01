// FUNC_NAME: PlayerSM::getMovementFlags
void __thiscall PlayerSM::getMovementFlags(int thisPtr, uint *outFlags)
{
  *outFlags = 0;
  if (*(char *)(thisPtr + 0x7c) != '\0') { // +0x7c: m_bMoveForward
    *outFlags = 1; // kMoveForward
  }
  if (*(char *)(thisPtr + 0x84) != '\0') { // +0x84: m_bMoveBackward
    *outFlags = *outFlags | 2; // kMoveBackward
  }
  if (*(char *)(thisPtr + 0x8c) != '\0') { // +0x8c: m_bStrafeLeft
    *outFlags = *outFlags | 4; // kStrafeLeft
  }
  return;
}