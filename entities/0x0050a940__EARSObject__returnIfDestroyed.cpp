// FUNC_NAME: EARSObject::returnIfDestroyed
void __fastcall EARSObject::returnIfDestroyed(int* objHandle)
{
    // objHandle is a pointer to a pointer to the object (e.g., a handle).
    // Offset +0x10c holds a flags field. Bit 0x20000 (bit 17) indicates destroyed/inactive state.
    // If set, the function returns immediately, acting as an early-out guard.
    if ((*(uint*)(*objHandle + 0x10c) & 0x20000) != 0) {
        return;
    }
    return;
}