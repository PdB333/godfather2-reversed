// FUNC_NAME: EARSObject::EARSObject
undefined4 * __thiscall EARSObject::EARSObject(undefined4 *this, byte allocatedFlag)
{
  // Set vtable pointer to class-specific vtable
  *this = &PTR_FUN_00e3f2c8;  // vtable for this class

  // Call base class constructor (likely EARSObjectBase or similar)
  FUN_004de130();  // Base constructor

  // If the object was heap-allocated (allocatedFlag == 1), free memory
  // This is a common EA pattern: if construction fails, deallocate
  if ((allocatedFlag & 1) != 0) {
    FUN_009c8eb0(this);  // operator delete or cleanup
  }

  return this;
}