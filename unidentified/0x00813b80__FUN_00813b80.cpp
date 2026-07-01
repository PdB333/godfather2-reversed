// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x00813900
  BaseClass::constructor();
  
  // If bit 0 of flags is set, call another initialization function with parameter 100
  if ((flags & 1) != 0) {
    // This likely initializes some capacity or count to 100
    SomeClass::initSomething(this, 100);
  }
  
  return this;
}