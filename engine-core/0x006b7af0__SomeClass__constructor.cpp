// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(SomeClass *this)
{
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d5e588; // +0x00 vtable
  
  // Set additional function pointers
  this->field_0x3c = &PTR_LAB_00d5e578; // +0x3c
  this->field_0x48 = &PTR_LAB_00d5e574; // +0x48
  
  // Initialize global state
  FUN_004086d0(&DAT_0120e93c); // Initialize some global object at 0x0120e93c
  FUN_0046c640();              // Initialize subsystem
}