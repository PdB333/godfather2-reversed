// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(EARSObject *this, byte flags)
{
  // Call base class constructor (likely at 0x0089d080)
  EARSObject::baseConstructor();
  
  // If bit 0 of flags is set, perform additional initialization
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // Might be a placement new or additional setup
  }
  
  return (undefined4)this;
}