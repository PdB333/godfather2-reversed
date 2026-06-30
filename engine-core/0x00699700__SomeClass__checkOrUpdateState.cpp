// FUNC_NAME: SomeClass::checkOrUpdateState
undefined1 __thiscall checkOrUpdateState(int this, undefined4 param_2, undefined4 param_3)
{
  undefined1 result;
  int *ptr;
  
  result = 0;
  ptr = (int *)FUN_00698c00(&param_2, param_2);
  if (*ptr != this + 4) {
    FUN_004d3e20(*ptr + 0x20);  // +0x20: some offset in the object
    result = FUN_004d6f20(&DAT_0120546e, param_3);
  }
  return result;
}