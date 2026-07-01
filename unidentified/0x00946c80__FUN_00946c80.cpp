// FUNC_NAME: SomeClass::getSomePointer
int SomeClass::getSomePointer(int param_1)
{
  int result = 0;
  if (((*(int *)(param_1 + 4) != 0) && (int innerPtr = *(int *)(*(int *)(param_1 + 4) + 4), innerPtr != 0)) &&
     (innerPtr = innerPtr + -0x48, innerPtr != 0)) {
    result = innerPtr;
  }
  return result;
}