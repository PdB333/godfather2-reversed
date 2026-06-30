// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(SomeClass *this)
{
  // Set vtable pointer to the class's vtable at 0x00e3adf0
  this->vtable = &PTR_FUN_00e3adf0;
  
  // Call base class or member initialization function
  FUN_00596650();
  
  return;
}