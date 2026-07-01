// FUNC_NAME: SomeClass::updateSomething
void __thiscall SomeClass::updateSomething(int thisPtr, undefined4 *outParam)
{
  undefined4 *localPtr;
  int someValue;
  undefined4 localVar;
  
  localPtr = outParam;
  *outParam = 2;
  outParam = (undefined4 *)0x0;
  localVar = 0;
  if (*(int *)(thisPtr + 0x50) == 0) {
    someValue = 0;
  }
  else {
    someValue = *(int *)(thisPtr + 0x50) + -0x48;
  }
  FUN_008f9e00(someValue, &outParam, &localVar, localPtr);
  *(undefined4 *)(thisPtr + 0x94) = *(undefined4 *)(thisPtr + 0x8c);
  *(undefined4 *)(thisPtr + 0x9c) = *(undefined4 *)(thisPtr + 0x90);
  *(undefined4 **)(thisPtr + 0x98) = outParam;
  *(undefined4 *)(thisPtr + 0xa0) = localVar;
  *(undefined4 *)(thisPtr + 0xa8) = 0;
  if (*(float *)(thisPtr + 0xa4) == 0.0) {
    *(undefined4 **)(thisPtr + 0x8c) = outParam;
    *(undefined4 *)(thisPtr + 0x90) = localVar;
  }
  return;
}