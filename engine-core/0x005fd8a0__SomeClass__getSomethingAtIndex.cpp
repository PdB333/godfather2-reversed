// FUNC_NAME: SomeClass::getSomethingAtIndex
void __thiscall getSomethingAtIndex(int thisPtr, int *index, int *outValue)
{
  int value;
  
  if (*(int *)(thisPtr + 0x70 + *index * 0xc) == 0) {
    value = 0;
  }
  else {
    value = *(int *)(thisPtr + *index * 0xc + 0x78);
  }
  if (value != 0) {
    *outValue = value;
  }
  return;
}