// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  *this = &PTR_FUN_00d78cf0;
  this[3] = &PTR_LAB_00d78c58;
  this[4] = &PTR_LAB_00d78c50;
  FUN_004086d0(&DAT_01206940);
  this[0x8a] = &PTR_LAB_00d78c34;
  FUN_004bec20();
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}