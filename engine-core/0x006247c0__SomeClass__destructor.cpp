// FUNC_NAME: SomeClass::destructor
undefined4 * __thiscall SomeClass::destructor(undefined4 *this, byte flags)
{
  int refCount;
  
  *this = &PTR_LAB_00e414e0; // vtable pointer
  refCount = FUN_00621530(this[2]); // likely decrement ref count on some sub-object
  *(short *)(refCount + 0x12) = *(short *)(refCount + 0x12) + -1; // decrement ref count at offset +0x12
  if ((flags & 1) != 0) {
    // operator delete if flag bit 0 set
    (**(code **)(**(int **)(DAT_012234ac + 4) + 4))(this, 0);
  }
  return this;
}