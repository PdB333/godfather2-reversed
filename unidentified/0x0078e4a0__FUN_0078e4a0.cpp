// FUNC_NAME: SomeClass::destructor
undefined4 * __thiscall SomeClass::destructor(undefined4 *this, byte flags)
{
  *this = &PTR_FUN_00d69b98; // vtable pointer
  this[3] = &PTR_LAB_00d69b94; // +0x0C: some member pointer
  FUN_004086d0(&DAT_012069c4); // likely release/cleanup some global resource
  if (this[4] != 0) { // +0x10: some pointer member
    FUN_009c8f10(this[4]); // release that member
  }
  this[3] = &PTR_LAB_00d69b90; // +0x0C: update pointer
  DAT_0112a68c = 0; // global flag
  FUN_004083d0(); // cleanup
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // operator delete
  }
  return this;
}