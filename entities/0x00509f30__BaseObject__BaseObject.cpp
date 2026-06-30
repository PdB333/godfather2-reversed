// FUNC_NAME: BaseObject::BaseObject
// Function address: 0x00509f30
// Role: Constructor for BaseObject class. Calls a common initialization routine,
//       then conditionally calls a finalization function based on a flag.
//       The flag parameter (bit 0) controls whether to perform additional setup.

uint32 __thiscall BaseObject::BaseObject(BaseObject* this, byte flags) {
    // Call base initialization routine (global or static)
    baseInit();

    // If the least significant bit of flags is set, perform additional construction
    if ((flags & 1) != 0) {
        finalizeConstruction(this);  // +0x00? (function takes this pointer)
    }

    return (uint32)this;  // Return the constructed object
}