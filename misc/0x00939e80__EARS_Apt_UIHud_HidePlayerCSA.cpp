// Xbox PDB: EARS_Apt_UIHud_HidePlayerCSA
// FUNC_NAME: PlayerSM::hidePlayerCSA
void __thiscall PlayerSM::hidePlayerCSA(int this) {
    // Broadcast "HidePlayerCSA" message/event
    // Parameters: messageName, int param=0, globalDataPtr (DAT_00d8a64c), int param2=0
    FUN_005a04a0("HidePlayerCSA", 0, &DAT_00d8a64c, 0);

    // Clear bit 0x100 (8) in flags at +0x5C
    *(uint *)(this + 0x5c) &= ~0x100;
}