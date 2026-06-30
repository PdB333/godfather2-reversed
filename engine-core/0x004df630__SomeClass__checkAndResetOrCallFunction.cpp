// FUNC_NAME: SomeClass::checkAndResetOrCallFunction
void __fastcall SomeClass::checkAndResetOrCallFunction(int *thisPtr)
{
  // Check if the first field (likely a flag or pointer) is non-zero
  if (*thisPtr != 0) {
    // If non-zero, call another function (likely a reset or cleanup routine)
    FUN_0051b3b0();
    return;
  }
  // If zero, do nothing
  return;
}