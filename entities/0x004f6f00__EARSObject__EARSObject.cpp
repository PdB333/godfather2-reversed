// FUNC_NAME: EARSObject::EARSObject
// 0x004f6f00 - Constructor for EARS engine base object with optional allocation/registration flag.
// param_1: this pointer (implicit)
// param_2: byte flag; if low bit is set, performs additional registration/acquisition via onAcquired()
__thiscall EARSObject::EARSObject(byte ownershipFlag)
{
    // Call base class initialization (likely sets default states or vtable)
    initBase(); // FUN_004f5d90

    // If ownershipFlag indicates the object should manage its own resources
    if (ownershipFlag & 1)
    {
        // Perform additional setup, possibly registering with a manager or allocating memory
        onAcquired(this); // FUN_009c8eb0
    }

    return this; // Return this pointer as per thiscall convention
}