// Xbox PDB: EARS_Apt_UIHud_SetCrewStatus
// FUNC_NAME: NPCCrewComponent::setCrewStatus
// Address: 0x00939860
// Role: Sets the crew status (none, follow, forcedFollow, inCombat) and logs the change.
// This method is called when a crew member's status changes. It checks if the component is active
// (flag at +0x48), then retrieves the current family manager singleton and stores the player's family
// ID (from familyManager+0xC4) into this+0x70. Finally, it logs the new status via the debug system.

void __thiscall NPCCrewComponent::setCrewStatus(int this, int param2, int status)
{
    int familyManager;
    char* statusStr;

    // Check if this crew component is active (e.g., crew leader flag)
    if (*(char*)(this + 0x48) != '\0') {
        familyManager = getFamilyManager(); // FUN_007351c0 - singleton getter
        if (familyManager != 0) {
            // Re-fetch (likely same instance) and store the player's family ID
            familyManager = getFamilyManager();
            *(int*)(this + 0x70) = *(int*)(familyManager + 0xC4); // +0xC4: current family ID or pointer
        }

        // Map status enum to string for logging
        switch (status) {
        case 0:
            statusStr = "none";
            break;
        case 1:
            statusStr = "follow";
            break;
        case 2:
            statusStr = "forcedFollow";
            break;
        case 3:
            statusStr = "inCombat";
            break;
        default:
            goto skipLog;
        }

        // Log the crew status change
        logCrewStatusChange("SetCrewStatus", 0, &DAT_00d8a64c, 1, statusStr); // FUN_005a04a0
    }
skipLog:
    return;
}