// FUNC_NAME: PlayerSM::updateStateTimers
void __fastcall PlayerSM::updateStateTimers(int thisPtr)
{
  byte flags;
  float fVar2;
  int local_8;
  
  FUN_007f0470(1);
  fVar2 = DAT_00d60d04;
  if (0.0 < *(float *)(thisPtr + 0xfe0)) {
    if (((*(byte *)(thisPtr + 0xfec) & 8) == 0) || (*(int *)(thisPtr + 0xfd4) == 0)) {
      local_8 = (int)(longlong)ROUND((1.0 - *(float *)(thisPtr + 0xfe0)) * DAT_00d60d04 + 1.0);
      *(int *)(thisPtr + 0xfd4) = local_8;
    }
    *(byte *)(thisPtr + 0xfec) = *(byte *)(thisPtr + 0xfec) | 8;
  }
  if (0.0 < *(float *)(thisPtr + 0xfe4)) {
    flags = *(byte *)(thisPtr + 0xfec);
    if (((flags & 4) == 0) || (*(int *)(thisPtr + 0xfd0) == 0)) {
      *(byte *)(thisPtr + 0xfec) = flags | 4;
      local_8 = (int)(longlong)ROUND((1.0 - *(float *)(thisPtr + 0xfe4)) * fVar2 + 1.0);
      *(int *)(thisPtr + 0xfd0) = local_8;
    }
    else {
      *(byte *)(thisPtr + 0xfec) = flags | 4;
    }
  }
  if ((*(int *)(thisPtr + 0x1bcc) != 0) &&
     (*(int *)(thisPtr + 0x1bcc) == **(int **)(thisPtr + 0x1bc8))) {
    FUN_007fbdf0(0);
    *(int *)(thisPtr + 0x1bcc) = 0;
  }
  *(int *)(thisPtr + 0x1f14) = 0;
  *(int *)(thisPtr + 0x1f18) = 0;
  return;
}