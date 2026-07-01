// FUNC_NAME: SomeClass::SomeMethod (constructor-like setup)
void __fastcall SomeClass::init(undefined4 *this)
{
  int iVar1;
  
  *this = &PTR_FUN_00d7ca70;
  iVar1 = FUN_006101a0(); // probably some singleton or global check
  if (iVar1 != 0) {
    FUN_00610100(this + 0x10); // likely sub-object initialization at offset +0x10
  }
  *this = &PTR_LAB_00e2f638; // update vtable or class pointer
  return;
}