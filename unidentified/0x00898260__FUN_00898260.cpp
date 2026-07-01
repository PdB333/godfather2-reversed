// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 *vtablePtr;
  int counter;
  
  vtablePtr = this + 1; // +0x4: vtable pointer
  DAT_01129988 = this; // store this pointer globally
  *vtablePtr = &PTR_LAB_00e30fe0; // set vtable
  *this = &PTR_FUN_00d77acc; // set another vtable
  *vtablePtr = &PTR_LAB_00d77abc; // override vtable
  counter = 6;
  do {
    FUN_00898070(); // call some initialization routine 7 times
    counter = counter + -1;
  } while (-1 < counter);
  FUN_00463980(0x73a2895d, vtablePtr, param_2); // register with hash 0x73a2895d
  return this;
}