// FUNC_NAME: SomeClass::someMethod
void __fastcall SomeClass::someMethod(int *thisPtr)
{
  char success;
  int *someObject;
  
  someObject = thisPtr;
  success = FUN_008b0830(thisPtr + 0x11, &someObject);
  if (success != '\0') {
    thisPtr[0x14] = 0;  // +0x50
    thisPtr[0x13] = 0;  // +0x4C
    thisPtr[0x12] = 0;  // +0x48
    thisPtr[0x11] = 0;  // +0x44
    thisPtr[0x10] = (int)someObject;  // +0x40 - store pointer
    (**(code **)(*someObject + 0xac))();  // call vtable method at offset 0xAC
    thisPtr[0xf] = *(int *)(DAT_01129908 + 0x14);  // +0x3C - copy from global
  }
  return;
}