// FUNC_NAME: EARSObject::copyFrom
void __thiscall EARSObject::copyFrom(EARSObject *this, EARSObject *other)
{
    // Delegates to the base implementation (0x00465700) which performs the actual copy
    EARSObject::copyFromImpl(this, other);
    return;
}