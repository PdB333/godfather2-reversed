// FUNC_NAME: EARSObject::shutdown
void __fastcall EARSObject::shutdown(int this)
{
    undefined4 local_10;
    undefined4 local_c;
    undefined4 *local_8;
    undefined1 local_4;

    // If the first resource pointer is non-null
    if (*(int *)(this + 0xd8) != 0) {
        // Clear bit 0 of flags at +0x84 (mask: 0xfffe)
        *(ushort *)(this + 0x84) = *(ushort *)(this + 0x84) & 0xfffe;

        // Release first resource
        if (*(int *)(this + 0xd8) != 0) {
            FUN_004df590();  // likely resource release step 1
            FUN_004df600();  // step 2
        }

        // Release second resource if present
        if (*(int *)(this + 0xdc) != 0) {
            FUN_004df590();
            FUN_004df600();
        }

        // Reset pointer and value
        *(int *)(this + 0xb0) = 0;
        *(int *)(this + 0xb4) = _DAT_00d5780c;  // some global constant

        local_10 = DAT_00d58cbc;  // another global

        // If bit 2 of flags is set (mask 0x04)
        if ((*(byte *)(this + 0x84) >> 2 & 1) != 0) {
            local_8 = &local_10;
            local_c = DAT_0112dbd0;  // some global
            local_4 = 0;
            FUN_00408a00(&local_c, 0);  // probably a debug/log function
        }

        FUN_00836700(local_10);  // likely a finalizer with the global value
    }

    return;
}