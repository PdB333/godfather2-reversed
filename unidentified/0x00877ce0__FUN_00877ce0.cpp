// FUNC_NAME: SomeClass::~SomeClass
/**
 * Destructor for a class with vtable at 0x00e2f0c0.
 * Cleans up a sub-object at offset +0x4, then optionally deallocates memory.
 * @param this unused? actually implicit this
 * @param param_2 Bit 0 controls whether to deallocate (call operator delete).
 */
undefined4 * __thiscall SomeClass::~SomeClass(SomeClass *this, byte param_2)
{
  // Check if sub-object pointer at +0x4 is non-null
  if (this->field_0x4 != (SomeSubObject *)0x0) {
    // Destroy sub-object
    FUN_004daf90(this + 1); // likely cleanup function for sub-object
  }
  // Restore vtable pointer (base class)
  this->vtable = (void *)&PTR_LAB_00e2f0c0;
  // If bit 0 set, deallocate memory
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this); // likely operator delete
  }
  return this;
}