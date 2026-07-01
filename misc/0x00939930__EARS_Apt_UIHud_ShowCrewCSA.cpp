// Xbox PDB: EARS_Apt_UIHud_ShowCrewCSA
// FUNC_NAME: CSACrewComponent::setShowCrewCSA
void __thiscall CSACrewComponent::setShowCrewCSA(void* thisPtr, int show) {
    // Check if the show flag is already set; bit 21 (0x15) of flags at +0x5C
    if (((*(uint*)((uint)thisPtr + 0x5C) >> 0x15) & 1) == 0) {
        // Store the show value at offset +0x80
        *(undefined4*)((uint)thisPtr + 0x80) = show;
        // Log the event – likely debug output
        FUN_005a04a0("ShowCrewCSA", 0, &DAT_00d8a64c, 0);
    }
    return;
}