// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(SomeClass *this, byte allocFlag)
{
  // Set vtable pointer (class-specific vtable at 0x00d76ad4)
  this->vtable = (void **)&PTR_FUN_00d76ad4;

  // Call base class constructors (likely EARSObject or similar)
  FUN_0087ff10();  // Base constructor 1
  FUN_008743d0();  // Base constructor 2

  // If allocFlag bit 0 is set, perform additional initialization or cleanup
  if ((allocFlag & 1) != 0) {
    FUN_009c8eb0(this);  // Possibly operator delete or placement new handler
  }

  return this;
}