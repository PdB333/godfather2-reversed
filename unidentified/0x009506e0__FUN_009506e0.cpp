// FUNC_NAME: SomeClass::getOrCreateCachedValue
int __fastcall getOrCreateCachedValue(int thisPtr)
{
  int uVar1;
  
  if (*(int *)(thisPtr + 0x154) == 0) {
    *(int *)(thisPtr + 0x178) = 0;
  }
  else if (*(int *)(thisPtr + 0x178) == 0) {
    uVar1 = FUN_006b0ee0(*(int *)(thisPtr + 0x154));
    *(int *)(thisPtr + 0x178) = uVar1;
    return uVar1;
  }
  return *(int *)(thisPtr + 0x178);
}