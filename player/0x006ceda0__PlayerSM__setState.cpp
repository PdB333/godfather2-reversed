// FUNC_NAME: PlayerSM::setState
void __thiscall PlayerSM::setState(int thisPtr, int state)
{
  if (state == 0) {
    *(int *)(thisPtr + 0xc4) = 0;  // +0xC4: stateId
    return;
  }
  *(int *)(thisPtr + 0xc4) = (state != 1) + 1;  // Maps state to 0,1,2
}