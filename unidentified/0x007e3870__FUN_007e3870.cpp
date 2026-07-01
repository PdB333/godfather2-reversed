// FUNC_NAME: SomeClass::SomeClass

undefined4 __thiscall SomeClass::SomeClass(undefined4 thisPtr, byte flags)
{
  SomeClass *self = (SomeClass *)thisPtr;

  // Call base class constructor (FUN_007e30b0)
  BaseClass::BaseClass();

  // If bit 0 of 'flags' is set, perform additional initialization
  if ((flags & 1) != 0) {
    self->extraInit(); // FUN_00624da0
  }

  return (undefined4)self;
}