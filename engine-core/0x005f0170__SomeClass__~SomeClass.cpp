// FUNC_NAME: SomeClass::~SomeClass
undefined4 * __thiscall SomeClass::~SomeClass(undefined4 *this, byte flags)
{
  // Set vtable to first destructor stage
  *this = &PTR_FUN_00e3fd80;
  
  // Release child object at offset 0x24C (0x93 * 4)
  if (this[0x93] != 0) {
    FUN_009c8f10(this[0x93]); // likely release/delete child
  }
  
  // Set vtable to base class
  *this = &PTR_LAB_00e3fd84;
  
  // Clear some global flag
  DAT_01223514 = 0;
  
  // If 'delete' flag is set, free memory
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // likely operator delete(this)
  }
  
  return this;
}