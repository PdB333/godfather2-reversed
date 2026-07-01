// FUNC_NAME: CoreObject::CoreObject(bool)
// Address: 0x0098fb20
// Role: Constructor for a base engine object (EARS-style), 
// calls a static initializer and optionally a setup function based on a boolean flag.

undefined4 __thiscall CoreObject::CoreObject(undefined4 this, byte initFlag)
{
  // Static initializer (likely base class or engine subsystem setup)
  EARSBase::staticInitializer(); // calls FUN_0098fa90
  // If the lowest bit of initFlag is set, run additional initialization on this object
  if ((initFlag & 1) != 0) {
    EARSBase::postCreationSetup(this); // calls FUN_009c8eb0
  }
  return this;
}