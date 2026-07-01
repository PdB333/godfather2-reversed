// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x007e8e60
  EARSObject::baseConstructor();
  
  // If bit 0 of flags is set, call operator delete with size 0x78 (120 bytes)
  // This is likely a placement new cleanup or custom deallocation
  if ((flags & 1) != 0) {
    operatorDelete(this, 0x78); // +0x00: size of EARSObject = 0x78
  }
  
  return this;
}