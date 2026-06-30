// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  *this = &PTR_FUN_00d5db44;
  this[1] = &PTR_LAB_00d5db34;
  FUN_004086d0(this + 0xfc); // likely initialize some member at +0xFC
  FUN_004086d0(&DAT_0112a578); // global static initialization
  FUN_004086d0(&DAT_0112b36c); // global static initialization
  FUN_004086d0(&DAT_0112a564); // global static initialization
  FUN_004086d0(&DAT_0112a56c); // global static initialization
  FUN_00408310(this + 0xfc); // likely destruct or reset member at +0xFC
  FUN_00408310(&DAT_0112a578); // global static cleanup
  FUN_00408310(&DAT_0112b36c); // global static cleanup
  FUN_00408310(&DAT_0112a564); // global static cleanup
  FUN_00408310(&DAT_0112a56c); // global static cleanup
  FUN_004083d0(); // some global initialization routine
  *this = &PTR_LAB_00d5dac8; // set vtable to final vtable
  DAT_0112a554 = 0; // global flag or counter reset
  return;
}