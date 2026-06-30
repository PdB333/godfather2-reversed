// FUNC_NAME: BaseManagedObject::destructor
undefined4 * __thiscall BaseManagedObject::destructor(undefined4 *this, byte deallocFlag)
{
  // Set vtable pointer (offset 0x0) to the appropriate function table
  *this = (undefined4 *)&PTR_FUN_00d5d9b0;

  // If sub-object at offset 0x34 (this[0xd]) exists, call its release function at offset 0x40 (this[0x10])
  if (this[0xd] != 0) {
    ((code *)this[0x10])(this[0xd]);
  }

  // If sub-object at offset 0x24 (this[0x9]) exists, call its release function at offset 0x30 (this[0xc])
  if (this[0x9] != 0) {
    ((code *)this[0xc])(this[0x9]);
  }

  // If sub-object at offset 0x14 (this[0x5]) exists, call its release function at offset 0x20 (this[0x8])
  if (this[0x5] != 0) {
    ((code *)this[0x8])(this[0x5]);
  }

  // If sub-object at offset 0x4 (this[0x1]) exists, call its release function at offset 0x10 (this[0x4])
  if (this[0x1] != 0) {
    ((code *)this[0x4])(this[0x1]);
  }

  // If deallocFlag has bit 0 set, free the memory using operator delete
  if ((deallocFlag & 1) != 0) {
    FUN_009c8eb0(this);
  }

  return this;
}