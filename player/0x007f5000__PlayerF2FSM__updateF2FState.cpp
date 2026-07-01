// FUNC_NAME: PlayerF2FSM::updateF2FState
void __thiscall PlayerF2FSM::updateF2FState(int thisPtr, char param_2)

{
  float fVar1;
  undefined4 local_8;
  
  fVar1 = *(float *)(thisPtr + 0x6d4); // +0x6D4: currentF2FValue (0.0-1.0)
  if (param_2 == '\0') {
    if (fVar1 < _DAT_00d5780c) { // _DAT_00d5780c: F2F threshold low
      if (((*(byte *)(thisPtr + 0x6dc) & 4) != 0) || (*(int *)(thisPtr + 0x6c0) == 0)) {
        local_8 = (undefined4)(longlong)ROUND(fVar1 * DAT_00d60d04 + _DAT_00d5780c);
        *(undefined4 *)(thisPtr + 0x6c0) = local_8; // +0x6C0: f2fTimer
      }
      *(byte *)(thisPtr + 0x6dc) = *(byte *)(thisPtr + 0x6dc) & 0xfb; // +0x6DC: flags, clear bit 2
    }
  }
  else if (_DAT_00d577a0 < fVar1) { // _DAT_00d577a0: F2F threshold high
    if (((*(byte *)(thisPtr + 0x6dc) & 4) == 0) || (*(int *)(thisPtr + 0x6c0) == 0)) {
      local_8 = (undefined4)(longlong)ROUND((1.0 - fVar1) * DAT_00d60d04 + 1.0);
      *(undefined4 *)(thisPtr + 0x6c0) = local_8; // +0x6C0: f2fTimer
    }
    *(byte *)(thisPtr + 0x6dc) = *(byte *)(thisPtr + 0x6dc) | 4; // +0x6DC: flags, set bit 2
    return;
  }
  return;
}