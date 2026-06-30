// FUNC_NAME: SomeClass::releaseOrFree
void __fastcall SomeClass::releaseOrFree(int *param_1)
{
  if (*param_1 != 0) {
    FUN_00414aa0(); // likely operator delete or release
  }
  return;
}