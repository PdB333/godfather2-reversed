// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte allocatingFlag)
{
  // Set vtable pointers (likely for multiple inheritance or interface dispatch)
  // +0x00: main vtable (PTR_FUN_00d8045c)
  // +0x3C: secondary vtable (PTR_LAB_00d8044c)
  // +0x48: tertiary vtable (PTR_LAB_00d80448)
  this[0] = (undefined4 *)&PTR_FUN_00d8045c;
  this[0xf] = (undefined4 *)&PTR_LAB_00d8044c;
  this[0x12] = (undefined4 *)&PTR_LAB_00d80448;

  // If the pointer at +0x60 (offset 0x18) is non-null, call a cleanup/release function
  // The function pointer is stored at +0x6C (offset 0x1b), called with the pointer itself
  if (this[0x18] != 0) {
    (*(code *)this[0x1b])(this[0x18]);
  }

  // Call base class constructor (likely EARS::Object or similar)
  FUN_0046c640();

  // If the allocation flag (bit 0) is set, call custom deallocation with size 400
  // This is typical for heap-allocated objects in EA engine
  if ((allocatingFlag & 1) != 0) {
    FUN_0043b960(this, 400);
  }

  return this;
}