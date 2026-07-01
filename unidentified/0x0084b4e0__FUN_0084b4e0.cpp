// FUNC_NAME: SomeClass::destructor
undefined4 * __thiscall SomeClass::destructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d74d54;
  // Set secondary vtable pointer (likely for a base class or interface)
  this[2] = &PTR_LAB_00d74d50;
  
  // Call some cleanup function on a static object at 0x00d74d40
  FUN_0049c7f0(&DAT_00d74d40);
  
  // If there's a child object at offset +0x0C, delete it
  if (this[3] != 0) {
    FUN_009c8f10(this[3]); // likely operator delete or destructor call
  }
  
  // Update secondary vtable pointer to another table
  this[2] = &PTR_LAB_00d74d4c;
  
  // Reset a global flag
  DAT_0112a668 = 0;
  
  // Call another cleanup function
  FUN_0049c640();
  
  // If the low bit of flags is set, free the memory (operator delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // likely operator delete
  }
  
  return this;
}