// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte flags)
{
  *this = &PTR_FUN_00e4448c;
  this[2] = &PTR_LAB_00e44498;
  (**(code **)(*(int *)this[3] + 0xc))();
  this[2] = &PTR_LAB_00e4449c;
  DAT_012234cc = 0;
  FUN_0049c640();
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}