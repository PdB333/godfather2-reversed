// FUNC_NAME: SomeClass::cleanupOrDestructor
void __fastcall SomeClass::cleanupOrDestructor(int *this)
{
  int iVar1;
  
  // Call base or helper cleanup
  FUN_0096abb0();
  
  // Release/release resource at this[5] (offset +0x14)
  FUN_009c8f10(this[5]);
  
  iVar1 = *this; // Dereference first member (likely a pointer)
  if (iVar1 != 0) {
    // Release resource at offset +0x08 of the pointed-to object
    FUN_009c8f10(*(int *)(iVar1 + 8));
    // Free the pointed-to object itself
    FUN_009c8eb0(iVar1);
  }
  return;
}