// FUNC_NAME: SomeClass::construct
// Address: 0x0066d7d0
// This function appears to be a constructor or initializer with an optional flag.
// It calls an initialization function (FUN_0066d7f0) and if the flag's lowest bit is set,
// calls a cleanup or deallocation function (FUN_009c8eb0). Returns this pointer.

void* SomeClass::construct(byte flag)
{
    // Call base or helper initialization (likely sets up member fields)
    this->baseInit(); // FUN_0066d7f0

    if (flag & 1)
    {
        // Delete or perform extra cleanup – possibly for exception handling or custom allocation
        this->destroyOrCleanup(); // FUN_009c8eb0
    }

    return this;
}