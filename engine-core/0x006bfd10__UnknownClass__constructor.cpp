// FUNC_NAME: UnknownClass::constructor
undefined4 * __thiscall CUnknownClass_ctor(undefined4 *this, byte flags)
{
  int *heapAlloc;

  *this = &PTR_FUN_00d5ee24;
  this[2] = &PTR_LAB_00d5ee1c;
  if (this[0x9c] != 0) {
    FUN_004daf90(this + 0x9c);  // likely freeing a sub-object at offset 0x270 (0x9c*4)
  }
  FUN_006d6500();  // unknown global initialization
  if ((flags & 1) != 0) {
    heapAlloc = (int *)FUN_009c8f80();
    (**(code **)(*heapAlloc + 4))(this, 0x280);  // operator new(0x280) via vtable
  }
  return this;
}