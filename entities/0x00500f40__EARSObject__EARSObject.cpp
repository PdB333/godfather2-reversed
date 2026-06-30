// FUNC_NAME: EARSObject::EARSObject

// Constructor for EARSObject base class.
// Calls base initialization (FUN_00500c10) and conditionally calls a destruction routine
// if the 'isHeapAllocated' flag (bit 0 of param_2) is set.
// This pattern is used to allow both heap-allocated and stack-allocated objects;
// if heap-allocated, the constructor can self-destruct on failure.

// Address: 0x00500f40
// Calling convention: __thiscall

void __thiscall EARSObject::EARSObject(EARSObject* this, byte flags)
{
    // Call the base class or low-level initialization
    EARSObject::initializeBase(); // FUN_00500c10

    // If the object was heap-allocated (bit 0 set), we must be ready to clean up
    if ((flags & 1) != 0)
    {
        // This likely calls operator delete or a destructor that frees memory
        EARSObject::destroyObject(this); // FUN_009c8eb0
    }

    // Return 'this' (implied by __thiscall)
    return;
}