// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor (likely EARS::Framework::Object or similar)
  EARSObject::baseConstructor(this);
  
  // If the 'delete after construct' flag (bit 0) is set, call operator delete
  if ((flags & 1) != 0) {
    EARSObject::operatorDelete(this, 0x430); // 0x430 = size of EARSObject
  }
  
  return this;
}