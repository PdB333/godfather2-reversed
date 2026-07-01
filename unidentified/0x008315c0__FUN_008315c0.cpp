// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass_constructor(undefined4 *this, byte flags)
{
  int *vtablePtr;
  
  *this = &PTR_FUN_00d73844;  // Set vtable pointer
  FUN_0082b490();              // Base class constructor call
  this[0xc] = &PTR_LAB_00e32854; // Set another vtable/interface pointer at offset 0x30 (0xc * 4)
  FUN_00821f60();              // Another initialization call
  if ((flags & 1) != 0) {
    vtablePtr = (int *)FUN_009c8f80(); // Get allocator function
    (**(code **)(*vtablePtr + 4))(this, 0xb0); // Call operator delete with size 0xB0
  }
  return this;
}