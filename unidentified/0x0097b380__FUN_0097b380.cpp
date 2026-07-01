// FUNC_NAME: SomeClass::setStateOrTimer
void __thiscall SomeClass::setStateOrTimer(int this, undefined4 param_2, int param_3)
{
  float fVar1;
  int iVar2;
  
  if (param_3 == 0) {
    fVar1 = (float)*(int *)(this + 0x150); // +0x150: some timer/counter
    if (*(int *)(this + 0x150) < 0) {
      fVar1 = fVar1 + DAT_00e44578; // adjust negative float
    }
    if (fVar1 == 0.0) goto LAB_0097b3c7;
    iVar2 = FUN_00494d10(); // likely getTickCount() or similar
    iVar2 = iVar2 + -1;
  }
  else {
    iVar2 = FUN_00494d10(); // getTickCount()
    iVar2 = iVar2 + param_3;
  }
  *(int *)(this + 0x150) = iVar2; // +0x150: timer/expiry value
LAB_0097b3c7:
  if (*(int *)(this + 0x14c) == 1) { // +0x14c: state flag
    *(undefined4 *)(this + 0x144) = param_2; // +0x144: some data/parameter
    return;
  }
  if ((*(int *)(this + 0x14c) != 0) && (*(int *)(this + 0x138) < 1)) { // +0x138: counter
    *(int *)(this + 0x138) = *(int *)(this + 0x138) + 1;
    FUN_005c0d50(this + 0x14, &LAB_00978de0, 0); // schedule callback
  }
  *(undefined4 *)(this + 0x144) = param_2; // +0x144: stored parameter
  *(undefined4 *)(this + 0x14c) = 1; // +0x14c: state flag set to 1
  FUN_005c0d50(this + 0x14, &LAB_0097b360, 0); // schedule another callback
  return;
}