// FUNC_NAME: SomeClass::someMethod
char __fastcall SomeClass::someMethod(int thisPtr)
{
  char result;
  int localArray[2];
  char localChar;

  *(char *)(thisPtr + 0x9a) = 0;
  result = FUN_006f6eb0(thisPtr);
  if (result == '\0') {
    if ((*(char *)(thisPtr + 0x9a) == '\0') &&
       (localArray[0] = *(int *)(thisPtr + 0x60), localArray[0] != 0)) {
      localArray[1] = 0;
      localChar = result;
      // Likely clearing some structure or array at offset 0x60
      FUN_00408a00(localArray, 0);
    }
    *(char *)(thisPtr + 0x9a) = 1;
  }
  return result;
}