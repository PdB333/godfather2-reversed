// FUNC_NAME: SomeEARSObject::constructor
// Function address: 0x008392e0
// Role: Constructor for an EARS engine object. Calls base class initializer (FUN_00838660) and optionally performs memory allocation of size 0x1a0 if a flag (param_2 & 1) is set.

undefined4 __thiscall SomeEARSObject::constructor(SomeEARSObject *this, byte allocationFlag)
{
  // Call base class initializer (likely common EARS object initialization)
  BaseClass::Initialize();

  // If the low bit of allocationFlag is set, allocate memory for additional data (size 0x1a0 bytes)
  if ((allocationFlag & 1) != 0) {
    EARSAlloc::AllocateMemory(this, 0x1a0);
  }

  return this;
}