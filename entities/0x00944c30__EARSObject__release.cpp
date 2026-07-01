//FUNC_NAME: EARSObject::release
void __fastcall EARSObject::release(int this) {
    // Check flag at offset +0xFE (bit 0 indicates sub-object needs cleanup)
    if ((*(byte *)(this + 0xfe) & 1) != 0) {
        FUN_00943a70(); // release sub-object (likely a child resource)
        *(ushort *)(this + 0xfe) &= 0xfffe; // clear the flag
    }
    // Prepare a temporary structure initialized from a global and call deallocation
    struct {
        int field0; // +0x00
        int field4; // +0x04
        char field8; // +0x08
    } local;
    local.field0 = DAT_011303e0; // global pointer or value
    local.field4 = 0;
    local.field8 = 0;
    FUN_00408a00(&local, 0); // likely a memory free or string release function
}