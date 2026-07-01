// FUNC_NAME: SomeEAObject::constructor
undefined4 * __thiscall SomeEAObject::constructor(undefined4 *this, byte flags)

{
  *this = &PTR_FUN_00d72f88;                 // vtable setup for this object
  this[0xf] = &PTR_LAB_00d72f78;              // +0x3C: pointer to some internal data (label)
  this[0x12] = &PTR_LAB_00d72f74;              // +0x48: another internal pointer (label)
  SomeEAObject::initialize(this);               // call internal initialization (FUN_00811b10)
  if ((flags & 1) != 0) {
    SomeEAObject::allocateMemory(this, 0x100);  // allocate 256 bytes if flag bit 0 is set (FUN_0043b960)
  }
  return this;
}