// FUNC_NAME: SomeClass::updateTimerOrState
undefined4 __thiscall SomeClass::updateTimerOrState(int this, float deltaTime)
{
  int *piVar1;
  char cVar2;
  int iVar3;
  float10 extraout_ST0;
  float fVar4;
  
  piVar1 = *(int **)(this + 0x50);
  cVar2 = FUN_0086c1b0();
  if (cVar2 != '\0') {
    iVar3 = *(int *)(*(int *)(this + 0x5c) + 0xb74);
    if ((iVar3 == 0) || ((*(byte *)(piVar1 + 0x32) & 1) != 0)) {
      if (*(float *)(this + 0x94) == DAT_00d5ccf8) {
        if (iVar3 == 0) {
          iVar3 = _rand();
          fVar4 = (float)iVar3 * DAT_00e44590 * DAT_00e445ac + _DAT_00d5780c;
        }
        else {
          fVar4 = 0.0;
        }
        *(float *)(this + 0x94) = fVar4;
      }
      deltaTime = *(float *)(this + 0x94) - deltaTime;
      *(float *)(this + 0x94) = deltaTime;
      if (deltaTime <= 0.0) {
        FUN_0086b830(0);
        FUN_0086b7b0(0);
        FUN_0086b7d0(0x3f800000);
        FUN_0086b7f0(1);
        FUN_0086b810(0);
        (**(code **)(**(int **)(*(int *)(this + 0x54) + 4) + 0x1b0))();
        if ((extraout_ST0 < (float10)DAT_00d75cc0) && (piVar1 != (int *)0x0)) {
          cVar2 = (**(code **)(*piVar1 + 0x44))();
          if (cVar2 != '\0') {
            *(float *)(this + 0x94) = DAT_00d5ccf8;
          }
        }
        return 1;
      }
    }
  }
  return 0;
}