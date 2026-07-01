// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor (likely EARS::Framework::Object or similar)
  FUN_009a3550();
  
  // If flag bit 0 is set, call additional initialization
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // Likely initializes vtable or other base data
  }
  
  return this;
}