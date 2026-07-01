// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte allocFlag)
{
  // Set vtable pointer (class-specific vtable at 0x00d76db0)
  *this = &PTR_LAB_00d76db0;
  // Call base class constructor (likely EARSObject or similar)
  BaseClass::constructor();
  // If allocFlag bit 0 is set, free memory (operator delete)
  if ((allocFlag & 1) != 0) {
    SomeClass::operatorDelete(this);
  }
  return this;
}