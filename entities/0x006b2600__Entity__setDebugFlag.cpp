// FUNC_NAME: Entity::setDebugFlag
void __thiscall Entity::setDebugFlag(bool enable)
{
    // EH setup: likely __try block with handler table at PTR_LAB_00d5dbb0
    // This is typical MSVC exception handling scaffolding
    undefined **local_14 = &PTR_LAB_00d5dbb0;
    int local_10 = this;
    undefined4 local_c;
    undefined1 *local_8 = (undefined1 *)&local_14;
    undefined1 local_4 = 0;

    if (enable) {
        // Set bit 2 (0x4) in flags at +0x34
        *(uint *)(this + 0x34) |= 4;
        local_c = DAT_0112a5f0;   // "debug draw enabled" string pointer
        local_8 = (undefined1 *)&local_14;
        FUN_00408a00(&local_c, 0); // log function (severity 0, message from DAT_0112a5f0)
    } else {
        // Clear bit 2
        *(uint *)(this + 0x34) &= 0xfffffffb;
        local_c = DAT_0112a5e8;   // "debug draw disabled" string pointer
        FUN_00408a00(&local_c, 0);
    }
}