// FUNC_NAME: SomeClass::logOrPrintMessage
void FUN_007e8ff0(int this, undefined4 param_2)
{
  undefined1 *message;
  undefined4 result;
  
  if (this != 0) {
    message = *(undefined1 **)(this + 0x6c);
    if (message == (undefined1 *)0x0) {
      message = &DAT_0120546e; // Default message string
    }
    result = FUN_004db3a0(param_2, message, *(undefined4 *)(this + 0x70));
    FUN_007e8e10(result);
  }
  return;
}