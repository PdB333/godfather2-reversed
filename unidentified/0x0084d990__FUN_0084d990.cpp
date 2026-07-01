// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  // Check if the pointer at this+4 is non-null
  if (this[1] != 0) {
    // Call destructor on the object at this+4
    FUN_004daf90(this + 1);
  }
  // Set vtable pointer to the base class vtable (PTR_LAB_00e2f0c0)
  *this = &PTR_LAB_00e2f0c0;
  return;
}