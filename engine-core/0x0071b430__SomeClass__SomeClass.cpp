// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x0071b430
// Constructor for SomeClass. Calls base initialization then conditionally performs additional setup based on flags (bit 0 of param2).
// param1 (this): pointer to object being constructed
// param2 (flags): byte flags; if bit 0 set, calls additional initialization function
// Returns: the this pointer (param1)

undefined4 __thiscall SomeClass::SomeClass(undefined4 this, byte flags)
{
  // Call base constructor/initialization (implicit this pointer in ECX)
  FUN_0071b220();  // SomeClass::initBase() - performs basic initialization

  // If the flag's LSB is set, perform additional initialization
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);  // SomeClass::extraInit() - handles extra setup
  }

  return this;
}