// FUNC_NAME: SomeClass::~SomeClass
undefined4 * __thiscall SomeClass::~SomeClass(undefined4 *this, byte deleteFlag)
{
  // Free member at offset +0x10 (param_1[4])
  if (this[4] != 0) {
    FUN_009c8f10(this[4]); // likely operator delete or custom free
  }
  // Free member at offset +0x4 (param_1[1])
  if (this[1] != 0) {
    FUN_009c8f10(this[1]);
  }
  // Set vtable pointer to base class (global vtable at 0x00d5c85c)
  *this = &PTR_LAB_00d5c85c;
  // Clear global flag (DAT_01129bb4)
  DAT_01129bb4 = 0;
  // If deleteFlag & 1, call deallocation function on this
  if ((deleteFlag & 1) != 0) {
    FUN_009c8eb0(this); // likely operator delete or scalar deleting destructor
  }
  return this;
}