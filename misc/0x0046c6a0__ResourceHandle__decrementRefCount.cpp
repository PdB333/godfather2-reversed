// FUNC_NAME: ResourceHandle::decrementRefCount
void __thiscall ResourceHandle::decrementRefCount(int *objectHeader)
{
    bool isSpecialMagic;

    // objectHeader[0] is a magic/type identifier compared to a global sentinel
    isSpecialMagic = (objectHeader[0] == g_specialMagic);

    // objectHeader[2] (byte) is a flag: 0 means normal release path
    if (((char)objectHeader[2] == '\0') &&
        (*(int *)(this + -4) != 0) &&   // +0(this) is handle itself; -4 is parent field (owner?
        (*(int *)(this + -8) != 0))     // -8 is another parent field (resource manager?)
    {
        // Call release on the object pointed to by parent's -4 field
        FUN_00482a50(*(undefined4 *)(this + -4), objectHeader, isSpecialMagic);
    }

    // If magic matches and both parent fields are non-null, clear them and call global cleanup
    if (isSpecialMagic &&
        (*(int *)(this + -4) != 0) &&
        (*(int *)(this + -8) != 0))
    {
        *(int *)(this + -8) = 0;   // clear parent field -8
        *(int *)(this + -4) = 0;   // clear parent field -4
        FUN_00482990();             // global cleanup (e.g., garbage collection tick)
    }
}