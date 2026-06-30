// FUNC_NAME: SomeClass::scalarDeletingDestructor
undefined4 * __thiscall SomeClass::scalarDeletingDestructor(undefined4 *this, byte deletingFlag)
{
  // Set vtable pointer (likely to base class vtable during destruction)
  *this = &PTR_FUN_00d60a08;

  // If member at offset +0xC (pointer) exists, release it with size 0x1ff (max items?)
  if (this[3] != 0) {
    FUN_004035f0(this[3], 0x1ff, this);
  }

  // Generic cleanup call
  FUN_006bcc90();

  // If member at offset +0x10 (pointer) exists, call its destructor via function pointer at offset +0x1C
  if (this[4] != 0) {
    (*(code *)this[7])(this[4]);
  }

  // Another cleanup call
  FUN_004083d0();

  // If the 'deleting' flag is set, free the memory (operator delete)
  if ((deletingFlag & 1) != 0) {
    FUN_009c8eb0(this);
  }

  return this;
}