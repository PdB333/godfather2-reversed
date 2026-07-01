// Xbox PDB: EARS_Apt_UIHud_HideObjective
// FUNC_NAME: ObjectiveUI::hideObjective
void __thiscall ObjectiveUI::hideObjective(ObjectiveUI *this)
{
    uint32 color; // from DAT_01130200
    uint32 zero8;
    uint8 zero4;

    // Send "HideObjective" command to the objective UI system
    FUN_005a04a0("HideObjective", 0, &DAT_00d8a64c, 0);

    // Clear bit 2 (0x4) of the flag at offset 0x5c, likely marking objective as hidden
    *(uint32 *)((uint8 *)this + 0x5c) &= 0xfffffffb;

    // Prepare color value (from global) and call a UI function (likely setting display properties)
    color = DAT_01130200;
    zero8 = 0;
    zero4 = 0;
    FUN_00408a00(&color, 0);
}