// FUNC_NAME: EARSObject::destructor
undefined4 * __thiscall EARSObject::destructor(undefined4 *this, byte flags)
{
  int iVar1;
  
  iVar1 = this[0xc]; // +0x30: some child object pointer
  *this = &PTR_FUN_00e39ff4; // vtable pointer for base class
  this[4] = &PTR_LAB_00e3a018; // +0x10: another vtable or function pointer
  if (iVar1 != 0) {
    FUN_00559ca0(iVar1); // likely child destructor
    FUN_009c8eb0(iVar1); // likely memory deallocation
  }
  this[4] = &PTR_LAB_00d987cc; // +0x10: reset to default
  *this = &PTR_LAB_00d96914; // vtable reset to base
  if ((flags & 1) != 0) {
    TlsGetValue(DAT_01139810); // get thread-local storage for allocator
    FUN_00aa26e0(this,*(undefined2 *)(this + 1),0x27); // operator delete with size
  }
  return this;
}