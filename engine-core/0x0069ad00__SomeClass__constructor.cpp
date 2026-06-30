// FUNC_NAME: SomeClass::constructor
// Address: 0x0069ad00
// Identity: Base class constructor with optional allocation control.
// Sets vtable pointer, initializes a subobject at offset 0x14, 
// then if the allocation flag (bit 0) is set, calls a deallocation function
// (likely to free memory if this is a placement-new wrapper).

SomeClass * __thiscall SomeClass::constructor(SomeClass *this, byte allocateFlag)
{
  // Set vtable pointer to class-specific vtable (address 0x00d5ce9c).
  this->vtablePtr = &PTR_FUN_00d5ce9c;

  // Initialize subobject at offset 0x14 (probably a pointer to a nested class or resource).
  // FUN_0069a0e0 is likely a constructor or init function for that subobject.
  FUN_0069a0e0(this->field_0x14);   // +0x14: subobject pointer

  // If the allocation flag bit 0 is set, call a deallocation function on this object.
  // This is typical for placement-new objects where allocation is separate.
  // FUN_009c8eb0 is probably operator delete (or a custom deallocator).
  if ((allocateFlag & 1) != 0) {
    FUN_009c8eb0(this);
  }

  return this;
}