// FUNC_NAME: EARSObject::EARSObject

// Constructor for an EARS engine object.
// param_1 (ECX) = this pointer
// param_2 = flags (bit 0: if set, registers object in global list)
undefined4 __thiscall EARSObject::EARSObject(undefined4 this, byte flags)
{
  // Call base class constructor
  BaseClass::BaseClass();

  // If the low bit of flags is set, register this object
  if ((flags & 1) != 0) {
    EARSObject::registerObject(this);
  }

  return this;
}