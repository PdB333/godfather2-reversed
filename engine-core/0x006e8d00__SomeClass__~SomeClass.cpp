// FUNC_NAME: SomeClass::~SomeClass
undefined4* __thiscall SomeClass::~SomeClass(undefined4* this, byte deleteFlag)
{
  // Set vtable to the destructor vtable (subobject destructor)
  *this = (undefined4*)&PTR_FUN_00d5fb78;

  // If sub-object at +0x0C is non-null, call its virtual destructor (first vtable entry) with argument 1
  if (this[3] != (undefined4*)0x0) {
    (**(code**)*((undefined4**)this[3]))(1);
  }

  // Restore vtable to base class vtable (or original vtable for non-deleting destructor)
  *this = (undefined4*)&PTR_LAB_00e2f638;

  // If delete flag is set, free the memory using operator delete
  if ((deleteFlag & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}