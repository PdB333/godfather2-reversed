// FUNC_NAME: SomeClass::compareOrAssert
undefined4 FUN_00622a60(void)

{
  int *thisPtr;
  int *otherPtr;
  
  if ((*otherPtr == 0) || (*otherPtr != *thisPtr)) {
    FUN_00b97aea(); // likely assertion failure or error handler
  }
  return CONCAT31((int3)((uint)otherPtr[1] >> 8),otherPtr[1] == thisPtr[1]);
}