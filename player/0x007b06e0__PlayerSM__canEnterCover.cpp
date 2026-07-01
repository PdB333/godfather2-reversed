// FUNC_NAME: PlayerSM::canEnterCover
undefined1 __thiscall PlayerSM::canEnterCover(int this, char param_2)
{
  char cVar1;
  
  cVar1 = FUN_00410eb0(); // likely isPlayerAlive() or similar
  if ((cVar1 != '\0') && (_DAT_00d5780c <= *(float *)(this + 0x1c8))) { // +0x1c8 = some height/position threshold
    if (param_2 == '\0') {
      if (*(float *)(this + 0x1c4) < _DAT_00d577a0) { // +0x1c4 = some movement/speed value
        return 0;
      }
    }
    else if (0.0 < *(float *)(this + 0x1c4) || *(float *)(this + 0x1c4) == 0.0) {
      return 0;
    }
    return 1;
  }
  return 0;
}