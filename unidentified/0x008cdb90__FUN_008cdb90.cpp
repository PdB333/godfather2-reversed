// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  int iVar1;
  int *piVar2;
  
  *this = &PTR_FUN_00d7ca00; // vtable setup for base class
  iVar1 = FUN_006101a0(); // likely some initialization check
  if (iVar1 != 0) {
    FUN_00610100(this + 8); // initialize member at offset +0x20 (8 * 4)
  }
  *this = &PTR_LAB_00e2f638; // vtable update to derived class
  if ((flags & 1) != 0) {
    piVar2 = (int *)FUN_009c8f80(); // get allocator
    (**(code **)(*piVar2 + 4))(this, 0xb0); // allocate 0xB0 bytes for this object
  }
  return this;
}