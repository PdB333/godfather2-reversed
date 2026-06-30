// FUNC_NAME: SomeClass::SomeClass
undefined4 * __thiscall SomeClass::SomeClass(SomeClass *this, byte flag)
{
  // Set vtable pointers: primary vtable at offset 0, secondary vtables at offsets 0x3C and 0x48
  *this = (undefined4 *)&PTR_FUN_00d5f45c;          // +0x00: primary vtable
  this[0xf] = (undefined4 *)&PTR_LAB_00d5f44c;      // +0x3C: secondary vtable
  this[0x12] = (undefined4 *)&PTR_LAB_00d5f448;     // +0x48: secondary vtable

  // Initialize sub-object at offset 0x50 (this + 0x14 in pointer units)
  FUN_004086d0(this + 0x14);
  FUN_00408310(this + 0x14);

  // Global initialization (possibly singleton or static data)
  FUN_0046c640();

  // If the flag has bit 0 set, call deallocation function (maybe placement delete or custom free)
  if ((flag & 1) != 0) {
    FUN_0043b960(this, 0x6c);  // size = 108 bytes
  }

  return this;
}