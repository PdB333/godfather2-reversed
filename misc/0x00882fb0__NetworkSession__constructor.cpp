// FUNC_NAME: NetworkSession::constructor
undefined4 * __thiscall NetworkSession::constructor(undefined4 *this, byte flags)
{
  *this = &PTR_LAB_00d76f00;
  FUN_0086aff0();
  if ((flags & 1) != 0) {
    FUN_00624da0(this);
  }
  return this;
}