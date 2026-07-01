// FUNC_NAME: SomeClass::updateSomething
void SomeClass::updateSomething(int *thisPtr)
{
  int result;
  
  result = (**(code **)(*thisPtr + 0x30))();
  if (result != 0) {
    result = (**(code **)(*thisPtr + 0x24))();
    if ((result != 0) && ((*(byte *)(thisPtr + 0x32) >> 5 & 1) == 0)) {
      FUN_0086d0b0();
      return;
    }
  }
  return;
}