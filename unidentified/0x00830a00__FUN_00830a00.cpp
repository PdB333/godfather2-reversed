// FUNC_NAME: SomeClass::SomeClass
undefined4 * __thiscall SomeClass::SomeClass(undefined4 *this, byte allocFlag)
{
  int *allocator;
  
  // Set primary vtable (base class)
  *this = &PTR_FUN_00d737b4;
  // Call base class constructor
  baseConstructor();
  // Set secondary vtable (interface or derived)
  this[0xc] = &PTR_FUN_00d7343c;
  // If sub-object pointer at offset 0x8C exists, destroy it
  if (this[0x23] != 0) {
    destroySubObject(this + 0x23);
  }
  // Override secondary vtable with derived class vtable
  this[0xc] = &PTR_LAB_00e32854;
  // Additional initialization
  init();
  // If allocFlag is set, allocate memory for this object (operator new)
  if ((allocFlag & 1) != 0) {
    allocator = (int *)getAllocator();
    (**(code **)(*allocator + 4))(this, 0xd0);
  }
  return this;
}