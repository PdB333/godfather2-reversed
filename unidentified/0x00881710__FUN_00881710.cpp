// FUNC_NAME: SomeClass::SomeClass
undefined4 * __thiscall SomeClass::SomeClass(SomeClass *this, byte param_2)
{
  // Set primary vtable pointer
  *this = &PTR_LAB_00d76cf0;  // +0x00: primary vtable

  // Set additional vtable pointers for multiple inheritance
  this[0x14] = &PTR_FUN_00d76cdc;  // +0x50: vtable for second base or interface
  this[0x17] = &PTR_LAB_00d76cd8;  // +0x5C: vtable for third base or interface

  // Call base class constructor (likely sets up other fields)
  FUN_008825e0();

  // If allocated via operator new (flag & 1), call operator delete on this
  if ((param_2 & 1) != 0) {
    FUN_00624da0(this);  // operator delete (likely)
  }

  return this;
}