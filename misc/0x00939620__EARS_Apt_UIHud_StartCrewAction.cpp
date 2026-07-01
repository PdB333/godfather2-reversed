// Xbox PDB: EARS_Apt_UIHud_StartCrewAction
// FUNC_NAME: PlayerCrewLeaderComponent::startCrewAction
void __thiscall PlayerCrewLeaderComponent::startCrewAction(undefined4 param_2, undefined4 param_3)
{
    // +0x48: flag indicating don mode is active (1 = active)
    if (*(char *)(this + 0x48) != '\0') {
        int iVar1 = getCrewManager(); // FUN_007351c0 - returns singleton CrewManager pointer
        if (iVar1 != 0) {
            iVar1 = getCrewManager(); // second call retrieves the same pointer
            // +0x70: pointer to current crew action (target/command)
            *(undefined4 *)(this + 0x70) = *(undefined4 *)(iVar1 + 0xc4);
        }
        // +0x7c: action target ID (e.g., building, NPC, position)
        *(undefined4 *)(this + 0x7c) = param_3;
        // Log the action start (debug/trace)
        debugPrint("StartCrewAction", 0, &DAT_00d8a64c, 0);
    }
}