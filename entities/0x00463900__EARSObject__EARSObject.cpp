// FUNC_NAME: EARSObject::EARSObject
unsigned int __thiscall EARSObject::EARSObject(EARSObject* this, byte flags)
{
    // Call the base initialization function (likely static or global)
    FUN_00463920();
    
    // If the least significant bit of flags is set, call additional initialization
    // +0x00: this pointer
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);  // secondary init or finalization
    }
    
    return this;
}