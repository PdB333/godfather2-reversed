// FUNC_NAME: SomeClass::releaseSlot
void __thiscall SomeClass::releaseSlot(int param_1, int param_2)
{
  int *piVar1;
  
  piVar1 = (int *)(param_1 + 0x1ac + *(int *)(param_2 + 0x184) * 8);
  if (*piVar1 != 0) {
    FUN_004daf90(piVar1);
    *piVar1 = 0;
  }
  return;
}