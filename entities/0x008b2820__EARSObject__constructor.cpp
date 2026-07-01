// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(EARSObject* this)
{
  // Set vtable pointer (base class virtual function table at address 0x00d7ace4)
  *this = (EARSObject*)&PTR_FUN_00d7ace4;

  // Set additional function pointer at offset +0x3C (0xF * 4)
  this->field_3C = &PTR_LAB_00d7acd4;

  // Set another pointer at offset +0x48 (0x12 * 4)
  this->field_48 = &PTR_LAB_00d7acd0;

  // Call a global function pointer (likely a static initializer)
  ((void (*)())PTR_FUN_00d7ad0c)();

  // Initialize some global manager or singleton at address 0x01218040
  FUN_00408310(&DAT_01218040);

  // Call another initialization function
  FUN_0046c640();
}