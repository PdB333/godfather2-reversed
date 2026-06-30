// FUNC_NAME: SomeClass::destructor
undefined4 * __thiscall SomeClass::destructor(undefined4 *this, byte flags)
{
  // Set vtable to first vtable pointer
  *this = &PTR_FUN_00d5fb78;
  
  // If the object at this[3] (offset +0x0C) is not null, call its destructor with parameter 1
  if ((undefined4 *)this[3] != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this[3])(1);
  }
  
  // Set vtable to second vtable pointer (base class or different vtable)
  *this = &PTR_LAB_00e2f638;
  
  // If the low bit of flags is set, deallocate memory
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}