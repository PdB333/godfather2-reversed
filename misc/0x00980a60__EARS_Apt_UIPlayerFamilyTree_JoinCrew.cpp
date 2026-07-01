// Xbox PDB: EARS_Apt_UIPlayerFamilyTree_JoinCrew
// FUNC_NAME: FamilyTreeManager::onAddCrewMember
void FamilyTreeManager::onAddCrewMember(void)
{
    int playerData;
    uint crewCount;
    char *message;
    void *dialog;

    // Check if game state is valid (not in mission or tutorial)
    if ((**(int **)(g_gameState + 4) == 0) || (**(int **)(g_gameState + 4) == 0x1f30)) {
        playerData = 0;
    }
    else {
        playerData = getPlayerData(g_playerManager); // FUN_0043b870
    }

    // Check if player can call crew (bit 0 of flag at +0x64)
    if ((*(byte *)(playerData + 0x64) & 1) == 0) {
        // Cannot call crew – show error
        dialog = createDialog(0xf0); // FUN_009c8e50
        if (dialog == 0) {
            dialog = 0;
        }
        else {
            dialog = initDialog(0); // FUN_00982280
        }
        message = "$pause_family_tree_cant_call_crew";
    }
    else {
        // Can call crew – check current crew count
        crewCount = getCurrentCrewCount(); // FUN_008bf540
        if (crewCount < *(uint *)(playerData + 0x34)) {
            // Under limit – show confirmation dialog
            dialog = createDialog(0xf0);
            if (dialog == 0) {
                dialog = 0;
            }
            else {
                dialog = initDialog(0);
            }
            setDialogMessage("$pause_family_tree_confirm_add"); // FUN_00981eb0
            *(int *)(dialog + 0xc) = 2; // Dialog type: confirm
            *(uint *)(dialog + 0x20) = 0xb9754031; // Callback hash for "yes"
            *(uint *)(dialog + 0x1c) = 0x997dee17; // Callback hash for "no"
            *(void **)(dialog + 0x14) = &onConfirmAddCrew; // LAB_0097f6e0
            showDialog(); // FUN_00982e10
            return;
        }
        // At max crew – show error
        dialog = createDialog(0xf0);
        if (dialog == 0) {
            dialog = 0;
            message = "$pause_family_tree_max_crew_reached";
        }
        else {
            dialog = initDialog(0);
            message = "$pause_family_tree_max_crew_reached";
        }
    }
    // Show error dialog
    setDialogMessage(message);
    *(int *)(dialog + 0xc) = 3; // Dialog type: error
    *(uint *)(dialog + 0x20) = 0x510c352b; // Callback hash for "ok"
    *(void **)(dialog + 0x14) = onErrorOk; // FUN_0097eca0
    showDialog();
    return;
}