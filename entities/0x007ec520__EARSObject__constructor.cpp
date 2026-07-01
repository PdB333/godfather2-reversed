// FUNC_NAME: EARSObject::constructor
void __thiscall EARSObject::constructor(undefined4 *this, int *vtablePtr, int param3)
{
  // Store the vtable pointer at offset 0x00
  *this = vtablePtr;
  
  // Call the virtual function at vtable+8 (likely a base class constructor or init)
  (**(code **)(*vtablePtr + 8))();
  
  // If param3 is non-zero, call FUN_004265d0 to initialize some resource/object
  // and store the result at offset 0x04
  if (param3 != 0) {
    this[1] = FUN_004265d0(param3, *this);
    return;
  }
  
  // Otherwise, set offset 0x04 to null
  this[1] = 0;
  return;
}