// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte initFlags)
{
  // Base class constructor call
  FUN_00500c10();
  
  // If bit 0 of initFlags is set, perform additional initialization
  if ((initFlags & 1) != 0) {
    // +0x00: Virtual table / object setup
    FUN_009c8eb0(this);
  }
  
  return this;
}