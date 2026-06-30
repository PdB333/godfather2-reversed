// FUNC_NAME: EARSObject::EARSObject

// Constructor for an EARSObject-derived class. Sets vtable, calls base class constructor,
// and optionally executes a cleanup or deallocation routine if the flag bit 0 is set.
// The flag likely indicates whether the object was heap-allocated (bit 0 = 1) or stack-allocated.
// vtable address: 0x00e3181c
// Base constructor: FUN_0064d5b0 (EARSObjectBase base class constructor)
// Cleanup: FUN_009c8eb0 (potentially operator delete or in-place destructor logic)
undefined4 * __thiscall EARSObject::EARSObject(undefined4 *this, byte flag)
{
  *this = (undefined4 *)&PTR_LAB_00e3181c;   // Set vtable pointer for this class
  baseConstructor(this);                      // Call base class constructor (EARSObjectBase)
  if ((flag & 1) != 0)
  {
    cleanupFunction(this);                    // Execute cleanup if heap-allocated flag
  }
  return this;                                // Return constructed object
}