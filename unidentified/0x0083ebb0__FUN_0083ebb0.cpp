// FUNC_NAME: SomeClass::resetOrClearState
void __fastcall SomeClass::resetOrClearState(int thisPtr)
{
  int iVar1;
  
  if ((*(byte *)(thisPtr + 0xac) & 1) == 0) {
    *(uint *)(thisPtr + 0xac) = *(uint *)(thisPtr + 0xac) | 1;
    if (((*(uint *)(thisPtr + 0xa8) >> 3 & 1) == 0) && ((*(uint *)(thisPtr + 0xa8) >> 4 & 1) != 0))
    {
      iVar1 = FUN_0083c160();
      if (0 < iVar1 + -1) {
        FUN_0083e1b0(iVar1 + -1);
      }
      *(undefined4 *)(thisPtr + 0xa0) = 0;
    }
  }
  return;
}