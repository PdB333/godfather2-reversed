// FUNC_NAME: EARSObject::EARSObject
// Constructor for an EARS base object. Calls global initialization and conditionally frees memory if flag bit 0 is set.
void* __thiscall EARSObject::EARSObject(byte flags)
{
    // Global initialization for the EARS system (ensures required subsystems are set up)
    someGlobalInit();

    // If the lowest bit of flags is set, deallocate this object immediately.
    // This pattern is typical for placement new where the allocation might be rolled back.
    if ((flags & 1) != 0)
    {
        operatorDelete(this);  // custom deallocation (likely operator delete or arena free)
    }

    return this;
}