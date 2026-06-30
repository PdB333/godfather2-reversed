// FUNC_NAME: EARSObject::~EARSObject
undefined4 * __thiscall EARSObject::~EARSObject(undefined4 *this, byte destructionFlags)
{
  char deallocResult;

  // Set vtable to purecall sentinel to prevent further virtual calls
  *this = &PTR___purecall_00e3edb4;

  // Release the pointer at offset +0x2C (e.g., a child object, reference count, or allocator data)
  if (this[0xb] != 0) {
    (*(void (__thiscall **)(undefined4 *))(DAT_0119caf4))(this[0xb]);  // call release function
  }
  this[0xb] = 0;

  // If destruction flags indicate to also delete this object (bit 0 set)
  if ((destructionFlags & 1) != 0) {
    deallocResult = FUN_005c43d0(this);  // custom deallocation (probably operator delete)
    if (deallocResult == '\0') {
      // If deallocation failed, fall back to some default handler via global table
      (**(code **)(**(int **)(DAT_012234ec + 4) + 4))(this, 0);
    }
  }
  return this;
}