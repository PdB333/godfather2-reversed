// Xbox PDB: EARS_Apt_UIHud_HideFanfare
// FUNC_NAME: someClass::hideFanfare
void __fastcall someClass::hideFanfare(int thisPtr)
{
    // Likely a destructor or cleanup method for a UI/hud element related to fanfare display
    FUN_0093f320(thisPtr + 0x84); // +0x84: some sub-object or member cleanup
    FUN_005a04a0("HideFanfare", 0, &DAT_00d8a64c, 0); // Send "HideFanfare" event/message
    *(uint *)(thisPtr + 0x5c) = *(uint *)(thisPtr + 0x5c) & 0xfffffffe; // +0x5c: clear bit 0 of flags (likely visible/active flag)
    return;
}