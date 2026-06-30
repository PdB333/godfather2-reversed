// FUNC_NAME: SomeClass::~SomeClass
undefined4 * __thiscall SomeClass::~SomeClass(undefined4 *this, byte shouldFree)
{
  // Set vtable to this class's vtable
  *this = (undefined4 *)&PTR_FUN_00d5d89c;
  
  // If the subobject pointer at offset 0xC is non-null, release it
  if (this[3] != 0) {
    // +0x0C: pointer to subobject (likely another class instance)
    releaseSubObject(this + 3);  // FUN_004daf90
  }
  
  // Set vtable to purecall (destructor completes, object becomes abstract)
  *this = (undefined4 *)&PTR___purecall_00e407a4;
  
  // If the "should free" flag is set (bit 0), deallocate memory
  if ((shouldFree & 1) != 0) {
    operatorDelete(this);  // FUN_009c8eb0
  }
  
  return this;
}