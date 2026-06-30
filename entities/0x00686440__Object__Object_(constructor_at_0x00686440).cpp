// FUNC_NAME: Object::Object (constructor at 0x00686440)
// This appears to be a constructor for a class with multiple vtable pointers.
// The object size is 0x70 (112 bytes).
// param_2 is a flag: if bit 0 is set, the object was heap-allocated and
// memory should be freed in case of failure (standard EA constructor pattern).

undefined4* __thiscall Object::Object(undefined4* this, byte allocFlag)
{
  // Assign primary vtable pointer (virtual function table)
  *this = &PTR_FUN_00d58958;

  // Assign secondary vtable pointer at offset +0x3C (0xF * 4)
  this[0xF] = &PTR_LAB_00d58948;

  // Assign another vtable or static data pointer at offset +0x48 (0x12 * 4)
  this[0x12] = &PTR_LAB_00d58944;

  // Call base class or common initialization routine
  // (presumably __thiscall with this as implicit parameter)
  FUN_00895330();

  // If the object was allocated on the heap (allocFlag & 1),
  // free memory on failure or during cleanup.
  // In the EA engine, this pattern allows the constructor to safely
  // deallocate memory if construction fails.
  if ((allocFlag & 1) != 0) {
    FUN_0043b960(this, 0x70); // deallocate(this, size)
  }

  return this;
}