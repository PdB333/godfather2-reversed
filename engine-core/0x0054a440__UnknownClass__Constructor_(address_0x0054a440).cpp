// FUNC_NAME: UnknownClass::Constructor (address 0x0054a440)
// This function is a constructor that first calls an initialization method (FUN_0054a460),
// then optionally invokes a cleanup function (FUN_009c8eb0) if the lowest bit of flags is set.
// The pattern suggests a factory or placement new scenario where the flag indicates
// whether the object should be freed upon construction failure.
UnknownClass* UnknownClass::Constructor(byte flags)
{
    // Call the internal initialization (likely base class setup)
    this->init();

    // If the lowest bit of the flags parameter is set, perform additional cleanup
    // (FUN_009c8eb0 is a destructor-like routine, possibly freeing memory)
    if (flags & 1)
    {
        this->cleanup();
    }

    return this;
}