// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte flags)
{
  *this = &PTR_FUN_00d57f30;
  FUN_004149b0();
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}