// FUNC_NAME: SomeClass::SomeClass
undefined4 * __thiscall SomeClass::SomeClass(undefined4 *this, byte param_2)
{
  int *allocatedMemory;
  
  // Set vtable pointer for primary base class
  *this = &PTR_FUN_00d7c188;
  // Set vtable pointer for secondary base class at offset 0x0C
  this[3] = &PTR_LAB_00d7c174;
  // Set vtable pointer for tertiary base class at offset 0x2C
  this[0xb] = &PTR_LAB_00d7c168;
  
  // Call base class constructor/initializer with global singleton
  FUN_004086d0(&DAT_012069d4);
  
  // Update tertiary vtable pointer after base initialization
  this[0xb] = &PTR_LAB_00d7c15c;
  
  // Call another base class initializer
  FUN_004b6250();
  
  // If param_2 has bit 0 set, allocate memory and call virtual function
  if ((param_2 & 1) != 0) {
    allocatedMemory = (int *)FUN_009c8f80(); // Allocate memory (likely operator new)
    // Call virtual function at offset 4 on the allocated object, passing this and size 0x50
    (**(code **)(*allocatedMemory + 4))(this, 0x50);
  }
  
  return this;
}