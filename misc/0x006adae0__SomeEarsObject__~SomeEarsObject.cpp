// FUNC_NAME: SomeEarsObject::~SomeEarsObject
undefined4 * __thiscall SomeEarsObject::~SomeEarsObject(undefined4 *this, byte deletingFlag)
{
  // Check if the pointer at offset +0x08 is non-null; if so, release it (likely a subobject or managed resource)
  if (this[2] != 0) {
    // FUN_004daf90 is a release/destroy function for that object
    FUN_004daf90(this + 2);
  }
  // Restore vtable pointer (after destruction, set to original vtable – common pattern for non-deleting path)
  *this = &PTR_LAB_00e2f0c0;
  // If the deleting flag (MSVC scalar deleting destructor convention: bit 0 set means delete this)
  if ((deletingFlag & 1) != 0) {
    // Call operator delete on this
    FUN_009c8eb0(this);
  }
  return this;
}