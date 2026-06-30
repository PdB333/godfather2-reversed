// FUNC_NAME: BaseClass::constructorWithInitFlag
undefined4 __thiscall BaseClass::constructorWithInitFlag(BaseClass *this, byte initFlag)
{
  // Call base initialization routine
  FUN_005e4360(); // likely parent constructor or basic setup

  // If initFlag has bit 0 set, call additional init (or cleanup?)
  if ((initFlag & 1) != 0) {
    FUN_009c8eb0(this); // possibly subclass-specific init or memory management
  }

  return (undefined4)this;
}