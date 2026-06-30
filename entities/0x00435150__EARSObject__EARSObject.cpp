// FUNC_NAME: EARSObject::EARSObject
EARSObject* __thiscall EARSObject::EARSObject(byte initFlags)
{
    // Call base class constructor / common initialization
    FUN_00435170();

    // If bit 0 of initFlags is set, perform additional cleanup or registration
    if ((initFlags & 1) != 0) {
        FUN_009c8eb0(this);  // e.g., register or release memory
    }

    return this;
}