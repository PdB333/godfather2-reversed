// FUNC_NAME: SomeClass::loadFromStream
void __thiscall SomeClass::loadFromStream(int thisPtr, int streamPtr)
{
  char hasMore;
  int tokenType;
  int readValue;
  int tokenPtr;

  FUN_0043b540(streamPtr);
  FUN_0043aff0(streamPtr, 0x3e3535d1);
  hasMore = FUN_0043b120();
  while (hasMore == '\0') {
    FUN_0043b210();
    tokenType = FUN_0043ab70();
    if (tokenType == 0) {
      FUN_0043b210();
      readValue = FUN_0043ab90();
      FUN_004089b0(thisPtr + 0x58, readValue);
    }
    else if (tokenType == 1) {
      tokenPtr = FUN_0043b210();
      *(int *)(thisPtr + 0x54) = *(int *)(tokenPtr + 8);
    }
    FUN_0043b1a0();
    hasMore = FUN_0043b120();
  }
  return;
}