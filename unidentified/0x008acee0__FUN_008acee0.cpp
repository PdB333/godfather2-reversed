// FUNC_NAME: SomeClass::destructor

void __fastcall SomeClass::destructor(int *this)
{
  int iVar1;
  
  // Call some base destructor or cleanup function
  FUN_008ab720();
  // Release/reference count decrement on member at offset 0x14 (param_1[5])
  FUN_009c8f10(this[5]);
  // If there's a pointer at offset 0x00, release its member at offset 0x08 and delete it
  iVar1 = *this; // +0x00
  if (iVar1 != 0) {
    FUN_009c8f10(*(undefined4 *)(iVar1 + 8)); // +0x08
    FUN_009c8eb0(iVar1);  // operator delete or similar deallocation
  }
  return;
}