// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte param_2)

{
  *this = &PTR_FUN_00d76304;
  FUN_00873bb0(0);
  *(undefined1 *)((int)this + 5) = 0;
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}