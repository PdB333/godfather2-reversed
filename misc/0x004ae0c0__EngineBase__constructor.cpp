// FUNC_NAME: EngineBase::constructor
void __fastcall EngineBase::constructor(EngineBase *this) 
{
  // Set the primary vtable pointer (offset +0x00)
  this->vtable = (void **)&PTR_FUN_00e356fc;
  // Set secondary vtable or state pointer at offset +0x08
  this->field_8 = &PTR_LAB_00e35708;
  // Call a virtual function (index 3, offset 0x0C) on an object pointed to by this->field_C (offset +0x0C)
  // The object at field_C has a vtable at its start.
  (**(code **)(*(int *)this->field_C + 0xc))();
  // Update the secondary vtable/state pointer again
  this->field_8 = &PTR_LAB_00e3570c;
  // Clear global startup flag
  g_globalInitFlag = 0; // _DAT_012234b0
  // Perform additional initialization
  FUN_0049c640(); // likely another constructor or setup function
  return;
}