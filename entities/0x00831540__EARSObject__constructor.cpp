// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(EARSObject *this)
{
  // Set vtable pointer to class-specific vtable
  this->vtable = &PTR_FUN_00d73844;
  
  // Call base class constructor
  FUN_0082b490();
  
  // Set another vtable pointer (likely for secondary interface or derived class)
  this->field_0x30 = &PTR_LAB_00e32854;
  
  // Call another initialization function
  FUN_00821f60();
  
  return;
}