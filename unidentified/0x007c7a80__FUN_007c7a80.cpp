// FUNC_NAME: SomeClass::~SomeClass
undefined4 * __thiscall SomeClass::~SomeClass(undefined4 *this, byte shouldDelete)
{
  // Set vtable to derived class vtable (0x00d6e930)
  *this = &PTR_FUN_00d6e930;
  
  // If the member at offset +8 (likely a pointer) is non-null, release it
  if (this[2] != 0) {
    FUN_004daf90(this + 2);  // releaseMember(this->somePointer)
  }
  
  // Set vtable to base class vtable (0x00d6ba68)
  *this = &PTR_LAB_00d6ba68;
  
  // If the delete flag is set, deallocate the object
  if ((shouldDelete & 1) != 0) {
    FUN_009c8eb0(this);  // operator delete(this)
  }
  
  return this;
}