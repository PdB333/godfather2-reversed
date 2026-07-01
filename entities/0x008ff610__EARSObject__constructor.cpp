// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(EARSObject *this)
{
  // Set vtable pointer
  *this = (EARSObject)&PTR_FUN_00d816e0;  // vtable assignment
  
  // Initialize member pointers at offsets +0x3C and +0x48
  this->field_0x3C = (void *)&PTR_LAB_00d816d0;  // +0x3C
  this->field_0x48 = (void *)&PTR_LAB_00d816cc;  // +0x48
  
  // Initialize sub-objects at offsets +0x58, +0x60, +0x68
  FUN_004086d0(&this->subObject_0x58);  // +0x58 - likely a list or array
  FUN_00408310(&this->subObject_0x58);  // +0x58 - initialize
  FUN_00408310(&this->subObject_0x60);  // +0x60 - initialize
  FUN_00408310(&this->subObject_0x68);  // +0x68 - initialize
  
  // Call global initialization function
  FUN_0046c640();  // likely a singleton or global state update
}