// FUNC_NAME: EARSObject::constructor
// Address: 0x004458f0 - Constructor for base EARS engine object.
// Calls base constructor at 0x00445910 and optionally initializes vtable/references if flag bit 0 is set.

undefined4 __thiscall EARSObject::constructor(EARSObject *this, byte constructFlags)
{
  // Call base class constructor (or core initialization routine)
  EARSObject::baseInit(this);
  
  // If the lowest bit of constructFlags is set, perform additional initialization
  // (e.g., set up virtual function table, allocate child objects, or register with manager)
  if ((constructFlags & 1) != 0) {
    EARSObject::initVTable(this);
  }
  
  return (undefined4)this;
}