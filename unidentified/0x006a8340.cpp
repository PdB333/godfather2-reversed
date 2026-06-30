// FUN_NAME: SomeClass::~SomeClass
undefined4 * __thiscall SomeClass::~SomeClass(undefined4 *this, byte flags)
{
  // Set the vtable pointer to a special cleanup vtable (base class or intermediate)
  *this = &PTR_FUN_00d5d89c;

  // Check if the resource pointer at offset 0xC (+0x0C) is non-null
  if (this[3] != 0) {
    // Release the resource (e.g., a heap-allocated buffer or managed object)
    releaseResource(this + 3);
  }

  // Set vtable to purecall handler to prevent further virtual calls after destruction
  *this = &PTR___purecall_00e407a4;

  // If the flags' low bit is set, deallocate the memory for this object
  if ((flags & 1) != 0) {
    deallocateMemory(this);
  }

  return this;
}