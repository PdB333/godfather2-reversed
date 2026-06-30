// FUNC_NAME: EARSObject::constructor
// Address: 0x004e6960
// Role: Constructor for an EARSObject. Calls base class initialization, then conditionally calls a cleanup/deallocation function based on the init flag.
// The initFlag parameter (byte) controls behavior: if the lowest bit is set, FUN_009c8eb0 (likely operator delete or finalizer) is invoked on this object.
// This pattern is typical for placement new with controlled memory management.

void* __thiscall EARSObject::constructor(void* this_ptr, byte initFlag)
{
    // Call base class constructor or initializer (FUN_004e6120)
    baseConstructor(this_ptr);

    // If the initFlag has the lowest bit set (meaning memory was externally allocated?),
    // free the object's memory or call a cleanup routine.
    if ((initFlag & 1) != 0) {
        // FUN_009c8eb0 is likely operator delete or a destructor that frees the memory
        freeObjectMemory(this_ptr);
    }

    return this_ptr;
}