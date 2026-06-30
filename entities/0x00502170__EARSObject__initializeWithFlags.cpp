// FUNC_NAME: EARSObject::initializeWithFlags
// Address: 0x00502170
// Role: Initializer / re-initializer with a flag that controls whether to call a cleanup/destructor-like function first
// Called with an existing instance (this) and a byte flags.
// If flags & 1, performs cleanup (likely a destructor or deallocation) via FUN_009c8eb0 before calling base init.

int __thiscall EARSObject::initializeWithFlags(byte flags)
{
    // Base class initialization (FUN_00501ab0)
    baseInitialize();  // +0x?? likely sets up vtable, members

    // If the low bit is set, call a cleanup/destruction function
    if (flags & 1)
    {
        cleanupOrDestroy();  // FUN_009c8eb0 - may free resources or call destructor chain
    }

    // Return the object pointer (same as 'this')
    return (int)this;
}