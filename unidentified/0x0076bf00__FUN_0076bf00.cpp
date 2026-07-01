// FUNC_NAME: SomeClass::~SomeClass
undefined4 * __thiscall SomeClass::~SomeClass(undefined4 *this, byte destructionFlags)
{
  // Set vtable pointer to class-specific vtable (for safe virtual dispatch during destruction)
  *this = &PTR_LAB_00d63090;

  // If the sub-object at offset 0x68 (0x1a * 4 bytes) is non-null, invoke its destructor
  if (this[0x1a] != 0) {
    FUN_004daf90(this + 0x1a);
  }

  // Perform global cleanup (likely engine-level resource release)
  FUN_0080ea60();

  // If the destruction flags indicate this is the final destructor, free the object's memory
  if ((destructionFlags & 1) != 0) {
    FUN_00624da0(this); // operator delete
  }

  return this;
}