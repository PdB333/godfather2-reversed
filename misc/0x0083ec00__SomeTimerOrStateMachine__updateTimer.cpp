// FUNC_NAME: SomeTimerOrStateMachine::updateTimer
void __thiscall SomeTimerOrStateMachine::updateTimer(int this, float dt)
{
  char cVar1;
  int iVar2;
  uint uVar3;
  float fVar4;
  
  FUN_0083de60();
  iVar2 = DAT_01129948;
  if ((*(uint *)(this + 0xac) >> 1 & 1) != 0) {
    return;
  }
  cVar1 = FUN_00842870();
  if (cVar1 == '\0') {
    if ((*(uint *)(iVar2 + 0x4c) >> 5 & 1) == 0) {
      fVar4 = *(float *)(this + 0xa4) - dt;
      *(float *)(this + 0xa4) = fVar4;
      if (fVar4 <= 0.0) {
        FUN_0083e370(*(undefined4 *)(this + 0x98));
        iVar2 = _rand();
        *(float *)(this + 0xa4) = ((float)iVar2 * DAT_00e44590 + _DAT_00d5c458) * DAT_00d5eee4;
      }
      if ((0.0 < *(float *)(this + 0xa0)) &&
         ((((*(byte *)(this + 0xa8) & 1) == 0 ||
           (iVar2 = *(int *)(this + 0x98), uVar3 = FUN_0083c160(),
           (uint)(*(int *)(this + 0x90) + iVar2) < uVar3)) &&
          (dt = *(float *)(this + 0xa0) - dt, *(float *)(this + 0xa0) = dt,
          dt < 0.0)))) {
        *(undefined4 *)(this + 0xa0) = 0;
      }
      if ((((*(uint *)(this + 0xa8) >> 3 & 1) == 0) && (*(float *)(this + 0xa0) == 0.0)) &&
         (*(int *)(this + 0x90) == 0)) {
        FUN_0083e1b0(1);
      }
      return;
    }
    return;
  }
  return;
}