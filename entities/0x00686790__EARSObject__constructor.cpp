// FUNC_NAME: EARSObject::constructor
// Function at 0x00686790 - Constructor for EARSObject (size 0x74)
// param_1: this pointer, param_2: flag (bit 0 indicates heap allocation)
undefined4 __thiscall EARSObject::constructor(EARSObject* this, byte isHeapAllocated)
{
    // Call base class constructor (0x008b2a40)
    baseConstructor(this); // placeholder for FUN_008b2a40

    // If the object was heap-allocated, deallocate memory after construction?
    // This is likely a cleanup for failed construction or a custom placement delete.
    if ((isHeapAllocated & 1) != 0) {
        // operator delete with size 0x74 (0x0043b960)
        operator delete(this, 0x74); // function at 0x0043b960
    }

    return this;
}