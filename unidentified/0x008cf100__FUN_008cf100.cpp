// FUNC_NAME: SomeClass::updateTimeOrSomething
void __thiscall SomeClass::updateTimeOrSomething(int this, float param_2)
{
  float fVar1;
  
  if (*(int *)(this + 0x20) == 0) {
    if (_DAT_00d5780c <= param_2) {
      FUN_00415200();
    }
    if (*(int *)(this + 0x20) == 0) goto LAB_008cf17a;
  }
  if (_DAT_00d5780c <= param_2) {
    fVar1 = param_2 * DAT_00e44640;
    FUN_004df890(fVar1 * fVar1 * fVar1 * fVar1 * fVar1);
    *(float *)(this + 0x3c) = param_2;
    return;
  }
  FUN_004153f0();
LAB_008cf17a:
  *(float *)(this + 0x3c) = param_2;
  return;
}