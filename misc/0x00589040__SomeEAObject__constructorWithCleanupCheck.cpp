// FUNC_NAME: SomeEAObject::constructorWithCleanupCheck
// Function address: 0x00589040
// This appears to be a constructor (or initializer) for an EA engine object.
// It first calls a base class initializer (0x00581a70), then conditionally calls
// a cleanup/destruction function (0x009c8eb0) based on the flag param_2.
// The flag likely indicates whether the object was dynamically allocated (1) or not (0),
// and if allocated, the cleanup function will properly release resources.
// However, note that this pattern is unusual; it may be a conditional initialization step.

undefined4 __thiscall SomeEAObject::constructorWithCleanupCheck(undefined4 this, byte cleanupFlag)
{
  // Call base class initializer (likely sets up base members)
  SomeBaseClass::baseInit();

  // If flag bit 0 is set, call a cleanup/deallocation function
  if ((cleanupFlag & 1) != 0) {
    SomeCleanupFunction(this);
  }
  return this;
}