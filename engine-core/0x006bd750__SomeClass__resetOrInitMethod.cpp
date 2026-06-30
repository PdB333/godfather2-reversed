// FUNC_NAME: SomeClass::resetOrInitMethod
void __fastcall SomeClass::resetOrInitMethod(int thisPtr)
{
  int iVar1;
  
  if (thisPtr == 0) {
    // If this is null, pass 0 to the sub-function
    iVar1 = 0;
  }
  else {
    // Otherwise, compute offset +0x50 from this
    iVar1 = thisPtr + 0x50;
  }
  // Call sub-function with computed pointer (likely initializes some sub-object at +0x50)
  FUN_00791350(iVar1);
  // Clear field at offset +0xD0 (likely a flag or pointer)
  *(undefined4 *)(thisPtr + 0xd0) = 0;
  return;
}