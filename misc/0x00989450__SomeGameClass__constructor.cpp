// FUNC_NAME: SomeGameClass::constructor
void __fastcall SomeGameClass::constructor(SomeGameClass *this)
{
  // Set vtable pointer
  *this = (SomeGameClass *)&PTR_FUN_00d915d8;
  // Set member pointers at offsets +0x10, +0x4C, +0x74
  this->field_0x10 = (void *)&PTR_LAB_00d915b0;  // +0x10
  this->field_0x4c = (void *)&PTR_LAB_00d915ac;  // +0x4C
  this->field_0x74 = (void *)&PTR_LAB_00d83b18;  // +0x74
  
  // Call base class constructor or initialization
  FUN_00407430();  // Some init function
  
  // Update member pointer at +0x4C
  this->field_0x4c = (void *)&PTR_LAB_00d91594;  // +0x4C
  
  // Set global static to 0
  DAT_0112992c = 0;  // Some global state flag
  
  // Another initialization call
  FUN_005c16e0();  // Some post-init function
}