// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  *this = &PTR_FUN_00d91070; // vtable pointer
  this[4] = &PTR_LAB_00d91048; // +0x10
  this[0x13] = &PTR_LAB_00d91044; // +0x4C
  if (this[0x30] != 0) { // +0xC0
    FUN_009c8f10(this[0x30]); // release some resource at +0xC0
  }
  this[0x13] = &PTR_LAB_00d91040; // +0x4C
  DAT_011305b0 = 0; // global flag
  FUN_005c16e0(); // cleanup/shutdown function
  return;
}