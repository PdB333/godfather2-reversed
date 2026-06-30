// FUNC_NAME: SomeClass::SomeClass
undefined4 * __thiscall SomeClass::SomeClass(undefined4 *this, byte flags)
{
  // Set vtable pointer for this class (first base)
  *this = &PTR_FUN_00d5c684;
  // Set vtable pointer for second base or interface
  this[3] = &PTR_LAB_00d5c680;
  // Increment global reference count or acquire lock
  incrementRefCount(&g_someGlobal);
  // If there is a callback object at offset 0x10 (this[4]), call its virtual function at offset 0xC
  if ((int *)this[4] != (int *)0x0) {
    (**(code **)(*(int *)this[4] + 0xc))();
  }
  // Change vtable pointer for second base to a different one (derived class)
  this[3] = &PTR_LAB_00d5c67c;
  // Reset global flag
  g_someFlag = 0;
  // Decrement global reference count or release lock
  decrementRefCount();
  // If the flags indicate deletion (bit 0 set), call the destructor/cleanup
  if ((flags & 1) != 0) {
    deleteObject(this);
  }
  return this;
}