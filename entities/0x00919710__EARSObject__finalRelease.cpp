// FUNC_NAME: EARSObject::finalRelease
void __thiscall EARSObject::finalRelease(void)
{
    // Call virtual function at vtable index 8 (vtable[2]) – likely a destroy or cleanup method
    ((void (*)(void))(this->vtable[2]))();
    // Call private cleanup routine at 0x00918500
    FUN_00918500();
    return;
}