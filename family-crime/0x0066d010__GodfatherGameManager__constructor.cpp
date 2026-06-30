// FUNC_NAME: GodfatherGameManager::constructor
void __fastcall GodfatherGameManager::constructor(GodfatherGameManager *this)
{
  // Set vtable for this object (first vtable pointer)
  this->vfptr = (void **)&PTR_FUN_00e4448c;
  // Set secondary vtable pointer (offset +0x08)
  this->vtable2 = (void **)&PTR_LAB_00e44498;
  // Call a virtual function on a subobject pointed to by this->field_0x0c (offset +0x0c)
  // The subobject's vtable function at offset 0x0c is invoked
  ((void (*)(void))(**(int (***)(void))(this->field_0x0c))[3])();
  // Adjust secondary vtable pointer after base class initialization (offset +0x08)
  this->vtable2 = (void **)&PTR_LAB_00e4449c;
  // Clear global initialization flag
  g_initializationFlag = 0;
  // Perform additional initialization
  FUN_0049c640();
}