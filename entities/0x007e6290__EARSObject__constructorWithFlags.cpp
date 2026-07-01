// FUNC_NAME: EARSObject::constructorWithFlags
undefined4 __thiscall EARSObject::constructorWithFlags(undefined4 this, byte flags)
{
  // Call base class constructor (0x007e5820)
  FUN_007e5820();
  
  // If the lowest bit of flags is set, perform additional initialization or cleanup
  // This is a common pattern in EA EARS engine for conditional sub-object construction
  if ((flags & 1) != 0) {
    // This call may be a destructor or another constructor step (0x00624da0)
    FUN_00624da0(this);
  }
  
  // Return this pointer (standard for constructors)
  return this;
}