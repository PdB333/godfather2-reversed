// FUNC_NAME: SomeClass::SomeClass
// Address: 0x006ca5b0
// Role: Constructor for a class derived from a base class (likely EARS object). 
//        Calls base constructor, then optionally performs additional initialization 
//        using a virtual function table pointer obtained from a static function.

undefined4 __thiscall SomeClass::SomeClass(byte flag)
{
  int *vtablePtr;
  
  // Call base class constructor
  BaseClass::BaseClass();
  
  // If bit 0 of flag is set, perform extra initialization
  if ((flag & 1) != 0) {
    // Get a pointer to a vtable or allocator structure
    vtablePtr = (int *)getVtablePointer();
    // Call a virtual function at offset 4 (likely a placement new or size allocation)
    // The second parameter 0xc0 (192) might be the size of this class
    (**(code **)(*vtablePtr + 4))(this, 0xc0);
  }
  
  return this;
}