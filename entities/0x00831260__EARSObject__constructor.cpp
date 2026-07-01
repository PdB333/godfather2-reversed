// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(EARSObject *this)
{
  // Set vtable pointer to EARSObject's vtable
  this->vtable = &PTR_FUN_00d73820;
  
  // Call base class constructor
  FUN_0082b1c0();
  
  // Set vtable pointer to derived class vtable (likely a subclass)
  this->vtable = &PTR_LAB_00e32854;
  
  // Call another initialization function
  FUN_00821f60();
  
  return;
}