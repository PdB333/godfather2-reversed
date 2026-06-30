// FUNC_NAME: SomeEARSClass::constructor
undefined4 __thiscall SomeEARSClass::constructor(SomeEARSClass *this, byte flags)
{
  // Call base class constructor at 0x0064f540
  BaseClass::constructor(this);

  // If flag bit 0 is set, call the destructor/vtable cleanup at 0x009c8eb0
  if ((flags & 1) != 0) {
    SomeEARSClass::destructor(this);
  }

  return this;
}