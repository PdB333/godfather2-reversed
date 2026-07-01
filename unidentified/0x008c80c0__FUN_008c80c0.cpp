// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(SomeClass *this)
{
  // Set vtable pointer to the class's virtual function table at 0x00d7bebc
  this->vtable = &PTR_LAB_00d7bebc;
  
  // Call base class constructor at 0x00791350
  FUN_00791350(this);
  
  return;
}