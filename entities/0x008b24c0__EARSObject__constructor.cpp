// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d7ac74; // EARSObject vtable
  // Initialize member fields at offsets +0x3C and +0x48
  this[0xf] = &PTR_LAB_00d7ac64; // +0x3C: some pointer
  this[0x12] = &PTR_LAB_00d7ac60; // +0x48: some pointer
  
  // Call base class or sub-object constructor
  FUN_008a1380(); // likely EARS::Framework::Object constructor
  
  // If the low bit of flags is set, call operator delete (or custom dealloc)
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 100); // operator delete(this, 0x64) - size 100 bytes
  }
  
  return this;
}