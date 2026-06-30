// FUNC_NAME: someClass::destructor
void __fastcall someClass_destructor(undefined4 *this)
{
  // Set vtable to the current class's vtable
  *this = &PTR_FUN_00e3e78c;
  
  // Call the destructor helper function
  FUN_005c0360();
  
  // Clear member at offset +0xC and +0x8
  this[3] = 0;
  this[2] = 0;
  
  // If the member at offset +0x4 is non-null
  if (this[1] != 0) {
    // Call a release function through the vtable of the object at this[1]
    (**(code **)(**(int **)(DAT_012234ec + 4) + 4))(this[1], 0);
  }
  
  // Reset member at offset +0x4 to NULL
  this[1] = 0;
  
  // Set vtable to the parent class's vtable
  *this = &PTR_LAB_00e3e74c;
  return;
}