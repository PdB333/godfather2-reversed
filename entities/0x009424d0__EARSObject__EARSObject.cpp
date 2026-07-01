// FUNC_NAME: EARSObject::EARSObject
// Function address: 0x009424d0
// Identified as a constructor for a base EARS object.
// Calls an initialization routine (FUN_00942250) and conditionally calls a destructor/cleanup (FUN_009c8eb0) based on a flag.
void* __thiscall EARSObject::EARSObject(byte flags) {
    // Call base class constructor or initialization (likely sets up vtable, members)
    FUN_00942250();
    // If the low bit of flags is set, call destructor or cleanup (e.g., for placement new with delete flag)
    if (flags & 1) {
        FUN_009c8eb0(this);
    }
    return this;
}