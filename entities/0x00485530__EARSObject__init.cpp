// FUNC_NAME: EARSObject::init
void* __thiscall EARSObject::init(void* thisPointer, byte flags)
{
    // Call base initialization function (likely sets up vtable or default members)
    EARSObject::baseInit(thisPointer);

    // If the low bit of flags is set, perform additional initialization
    if (flags & 1)
    {
        // Secondary initialization (possibly derived class setup or resource allocation)
        FUN_009c8eb0(thisPointer);
    }

    return thisPointer;
}