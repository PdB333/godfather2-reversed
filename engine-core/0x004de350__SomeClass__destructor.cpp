// FUNC_NAME: SomeClass::destructor
undefined4 * __thiscall SomeClass_destructor(undefined4 *this, byte flags)

{
  // Set vtable to first class's vtable (base class cleanup)
  *this = &PTR_FUN_00e36f1c;
  
  // Check if the pointer at +0x4 is non-null and call its virtual destructor at offset 0xC
  if ((int *)this[1] != (int *)0x0) {
    (**(code **)(*(int *)this[1] + 0xc))();
  }
  
  // Set vtable to second class's vtable (derived class cleanup)
  *this = &PTR_LAB_00e362b8;
  
  // If flag bit 0 is set, free the memory (operator delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);   // likely operator delete or custom dealloc
  }
  
  return this;
}