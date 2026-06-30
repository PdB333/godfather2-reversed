// FUNC_NAME: SomeClass::resetOrClear
void SomeClass::resetOrClear(undefined4 *thisPtr)
{
  if (thisPtr != (undefined4 *)0x0) {
    FUN_005f2230(1);
    if (thisPtr[0xb] != 0) {
      *(undefined4 *)(thisPtr[0xb] + 8) = 0;
      if (thisPtr[2] != 0) {
        FUN_005e4cf0();
      }
      thisPtr[0xb] = 0;
    }
    thisPtr[2] = 0;
    thisPtr[0xc] = 0;
    thisPtr[0x1a] = 0;
    thisPtr[0x18] = 0;
    thisPtr[0xd] = 0;
    FUN_005f57b0();
    if (DAT_011a0f00 != 0) {
      *thisPtr = DAT_011a0efc;
      DAT_011a0f08 = DAT_011a0f08 + 1;
      DAT_011a0efc = thisPtr;
    }
    FUN_005dbc10(*(undefined1 *)(thisPtr + 0x19),thisPtr[0x17],*(undefined1 *)((int)thisPtr + 0x65),
                 DAT_011a0efa);
  }
  return;
}