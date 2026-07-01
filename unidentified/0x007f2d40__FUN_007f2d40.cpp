// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  // Set vtable pointer to destructor vtable (likely a base class destructor vtable)
  *this = &PTR_FUN_00d70298;
  // Set another vtable pointer to a different vtable (likely a secondary base or member)
  this[2] = &PTR_LAB_00d70294;
  
  // Call virtual function at offset 0xC on the object pointed to by this[3]
  // This is likely releasing a sub-object or calling a cleanup method
  (**(code **)(*(int *)this[3] + 0xc))();
  
  // Call virtual function at offset 4 on the object pointed to by this[8], passing this[4] and 0
  // This is likely a release or delete method for a resource
  (**(code **)(*(int *)this[8] + 4))(this[4], 0);
  
  // If this[7] is non-null, call the same virtual function on it as well
  if (this[7] != 0) {
    (**(code **)(*(int *)this[8] + 4))(this[7], 0);
  }
  
  // Call virtual function at offset 0xC on the object pointed to by this[8]
  // This is likely final cleanup for the resource manager
  (**(code **)(*(int *)this[8] + 0xc))();
  
  // Set vtable pointer to a third vtable (likely the final destructor vtable)
  this[2] = &PTR_LAB_00d7028c;
  
  // Reset a global flag to 0
  DAT_01129968 = 0;
  
  // Call a cleanup function (likely deinitializing some subsystem)
  FUN_0049c640();
  
  return;
}