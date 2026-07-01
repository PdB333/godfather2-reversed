// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte flags)
{
  int *vtablePtr;
  
  *this = &PTR_FUN_00d7388c;  // Set vtable pointer
  FUN_0082ba50();              // Base class constructor
  this[0xc] = &PTR_LAB_00e32854; // Set another vtable pointer at offset +0x30
  FUN_00821f60();              // Another initialization call
  if ((flags & 1) != 0) {
    vtablePtr = (int *)FUN_009c8f80(); // Get allocator
    (**(code **)(*vtablePtr + 4))(this, 0xa0); // Call operator delete with size 0xA0
  }
  return this;
}