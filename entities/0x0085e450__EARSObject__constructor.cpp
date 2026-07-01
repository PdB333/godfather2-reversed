// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte param_2)
{
  // Call base class constructor at 0x0085e0d0
  EARSObject::baseConstructor(this);
  
  // If param_2 has bit 0 set, call destructor at 0x009c8eb0
  if ((param_2 & 1) != 0) {
    EARSObject::destructor(this);
  }
  
  return this;
}