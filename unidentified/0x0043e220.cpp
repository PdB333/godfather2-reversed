// FUN_0043e220: EARSObject::EARSObject(uint8 flags)
__thiscall EARSObject::EARSObject(uint8 flags)
{
    // Call base constructor or common initialization (FUN_0043e250)
    baseInit();

    // If the low bit of flags is set, perform additional cleanup (likely destructor or uninit)
    if (flags & 1)
    {
        deleteObject(this); // FUN_009c8eb0
    }

    // Compiler-generated return of this (implicit in real constructors)
    return this;
}