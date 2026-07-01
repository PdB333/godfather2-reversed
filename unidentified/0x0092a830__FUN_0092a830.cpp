// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  *this = &PTR_FUN_00d88760; // vtable pointer
  this[4] = &PTR_LAB_00d88738; // +0x10
  this[0x13] = &PTR_LAB_00d88734; // +0x4C
  FUN_009c8f10(this[0x41]); // +0x104 - release resource
  FUN_009c8f10(this[0x42]); // +0x108 - release resource
  FUN_009c8f10(this[0x43]); // +0x10C - release resource
  FUN_009c8f10(this[0x44]); // +0x110 - release resource
  FUN_009c8f10(this[0x45]); // +0x114 - release resource
  if (this[0x4e] != 0) { // +0x138 - pointer check
    FUN_004daf90(this + 0x4e); // +0x138 - delete object
  }
  if (this[0x46] != 0) { // +0x118 - pointer check
    FUN_009c8f10(this[0x46]); // +0x118 - release resource
  }
  this[0x1b] = &PTR_LAB_00d83b18; // +0x6C - set vtable
  this[0x13] = &PTR_LAB_00d88730; // +0x4C - set vtable
  DAT_011304f8 = 0; // global flag reset
  FUN_005c16e0(); // cleanup/notification
  return;
}