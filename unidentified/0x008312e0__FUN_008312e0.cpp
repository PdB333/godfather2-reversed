// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags) {
  int *piVar1;
  
  // Set vtable pointer (Base class)
  *this = &PTR_FUN_00d73820;
  
  // Call base class constructor
  FUN_0082b1c0();
  
  // Set own vtable pointer
  this[0xc] = &PTR_LAB_00e32854;
  
  // Call member initialization
  FUN_00821f60();
  
  // If the flag indicates we should allocate, allocate memory
  if ((flags & 1) != 0) {
    piVar1 = (int *)FUN_009c8f80();   // operator new or allocator
    (**(code **)(*piVar1 + 4))(this, 0xd0);  // call placement new or copy constructor with size 0xD0
  }
  
  return this;
}