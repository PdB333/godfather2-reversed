// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  *this = &PTR_FUN_00d5c4d8; // vtable pointer
  this[3] = &PTR_LAB_00d5c4d4; // some member pointer
  FUN_00408310(&DAT_01129aa0); // likely release/delete
  FUN_00408310(&DAT_01129a98); // likely release/delete
  FUN_004086d0(&DAT_012069b4); // likely release/delete
  FUN_004086d0(&DAT_012069c4); // likely release/delete
  if (this[7] != 0) { // +0x1C - some pointer member
    (*(code *)this[10])(this[7]); // +0x28 - function pointer, call destructor on member
  }
  this[3] = &PTR_LAB_00d5c4d0; // update member pointer
  DAT_01129814 = 0; // global flag
  FUN_004083d0(); // likely cleanup function
  return;
}