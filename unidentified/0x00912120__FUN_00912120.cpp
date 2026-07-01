//FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flag)
{
  // Call base class constructor at 0x00911d50
  FUN_00911d50();
  
  // If flag bit 0 is set, call vtable setup or additional initialization
  if ((flag & 1) != 0) {
    FUN_005c4480(this);
  }
  
  return this;
}