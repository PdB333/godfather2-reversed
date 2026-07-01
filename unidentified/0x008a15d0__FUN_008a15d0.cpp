// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(SomeClass *this)
{
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d78cf0; // +0x00
  // Set other function pointers
  this->field_0x0c = &PTR_LAB_00d78c58; // +0x0C
  this->field_0x10 = &PTR_LAB_00d78c50; // +0x10
  // Call some initialization function with a global data pointer
  FUN_004086d0(&DAT_01206940);
  // Set another function pointer at offset 0x228 (0x8a * 4)
  this->field_0x228 = &PTR_LAB_00d78c34; // +0x228
  // Call another initialization function
  FUN_004bec20();
}