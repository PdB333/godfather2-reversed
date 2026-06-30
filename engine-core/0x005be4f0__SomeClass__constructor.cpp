// FUNC_NAME: SomeClass::constructor
undefined4 * __fastcall SomeClass::constructor(undefined4 *this)
{
  this[1] = 0;
  *this = &PTR_FUN_00e3e52c; // vtable pointer
  FUN_0049c6e0(&DAT_00e3e46c, 1); // Initialize some resource/flag at 0x00e3e46c
  FUN_0049c6e0(&DAT_00e3e470, 1); // Initialize some resource/flag at 0x00e3e470
  FUN_0049c6e0(&PTR_LAB_00e3e474, 1); // Initialize some resource/flag at 0x00e3e474
  FUN_0049c6e0(&DAT_00e3e478, 1); // Initialize some resource/flag at 0x00e3e478
  return this;
}