// FUNC_NAME: UnknownClass::getContainerOrParent
int __fastcall UnknownClass::getContainerOrParent(int thisPtr)
{
    // Check if the pointer stored at +0xBC is non-null
    // That pointer likely points to an embedded member or a container object.
    // Subtract 0x48 to obtain the base object (common pattern for recovering
    // the containing object from a sub-object offset in multiple inheritance).
    int* containerPtr = *(int**)(thisPtr + 0xBC);
    if (containerPtr != (int*)0) {
        // Return the base address of the container (e.g., the enclosing class instance)
        return (int)(containerPtr - 0x48); // Cast to int for pointer arithmetic
    }
    return 0;
}