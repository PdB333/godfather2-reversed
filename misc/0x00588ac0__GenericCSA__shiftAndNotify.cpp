// FUNC_NAME: GenericCSA::shiftAndNotify
void GenericCSA::shiftAndNotify(int startIndex)
{
  int iVar1;
  undefined4 *ediPtr;
  
  for (iVar1 = startIndex - (int)ediPtr; 1 < iVar1 >> 2; iVar1 = iVar1 + -4) {
    *(undefined4 *)((int)ediPtr + iVar1 + -4) = *ediPtr;
    FUN_00588cb0();
  }
  return;
}