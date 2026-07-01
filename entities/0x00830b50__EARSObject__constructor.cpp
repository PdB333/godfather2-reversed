// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte flags)
{
  int *vtablePtr;
  
  *this = &PTR_FUN_00d737d8;  // Set vtable pointer
  FUN_0082a9d0();              // Base class constructor call
  this[0xc] = &PTR_LAB_00e32854; // Set another vtable pointer at +0x30
  FUN_00821f60();              // Additional initialization
  if ((flags & 1) != 0) {
    vtablePtr = (int *)FUN_009c8f80(); // Allocate memory (operator new)
    (**(code **)(*vtablePtr + 4))(this, 0xc0); // Call placement delete on failure
  }
  return this;
}