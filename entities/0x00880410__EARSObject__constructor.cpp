// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(EARSObject *this)
{
  // Set vtable pointer to base class vtable (PTR_FUN_00d76bc0)
  this->vtable = &PTR_FUN_00d76bc0;
  
  // Call base class constructor (likely EARS::Framework::Object or similar)
  FUN_0043e380(this);
  
  // Override vtable with derived class vtable (PTR_LAB_00e30ea0)
  this->vtable = &PTR_LAB_00e30ea0;
  
  return;
}