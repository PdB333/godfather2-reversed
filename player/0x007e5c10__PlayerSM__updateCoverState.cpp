// FUNC_NAME: PlayerSM::updateCoverState
void __fastcall PlayerSM::updateCoverState(int thisPtr)
{
  int playerPtr;
  Vector3 local_24;
  Vector3 local_18;
  Vector3 local_c;

  if (*(int *)(thisPtr + 0xf0) == 0) {
    playerPtr = 0;
  }
  else {
    playerPtr = *(int *)(thisPtr + 0xf0) + -0x48;
  }
  FUN_007ab6b0(playerPtr);
  FUN_007ab2f0(thisPtr + 0x100);
  playerPtr = *(int *)(thisPtr + 0x58);
  if (((*(uint *)(playerPtr + 0x8e0) >> 4 & 1) == 0) &&
     (((*(uint *)(playerPtr + 0x8e0) >> 0x19 & 1) == 0 || ((*(uint *)(playerPtr + 0x8e8) >> 2 & 1) != 0))))
  {
    FUN_007e4e00(&local_24, thisPtr + 0x80, thisPtr + 0x8c, playerPtr);
    FUN_007e5910(&local_18, &local_24, thisPtr + 0x8c, *(undefined4 *)(thisPtr + 0x58));
    FUN_007e59a0(&local_c, &local_18, &local_24, *(undefined4 *)(thisPtr + 0x58));
    FUN_0072a0b0(&local_c);
  }
  return;
}