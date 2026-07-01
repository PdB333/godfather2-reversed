//FUNC_NAME: ActionManager::processActions
void __fastcall ActionManager::processActions(int this) {
    int *pActionListHead;
    char cVar2;
    int iVar3;
    int iVar4;
    undefined4 *pCurrentAction;
    undefined4 local_10;
    undefined4 local_c;
    undefined1 local_8[4];
    int local_4;

    // Check if action count is non-zero (offset +0x34)
    if (*(int *)(this + 0x34) != 0) {
        // Get the head of the action list (offset +0x30)
        pActionListHead = (int *)**(int **)(this + 0x30);
        local_4 = (int)pActionListHead;

        // Assertion checks: ensure list head is valid
        if (pActionListHead == *(int **)(this + 0x30)) {
            FUN_00b97aea(); // likely __debugbreak or assertion
        }
        if (pActionListHead == (int *)*(int *)(this + 0x30)) {
            FUN_00b97aea();
        }

        // Extract action ID from head node (offset +0x0C)
        local_10 = pActionListHead[3];
        // Initialize action (FUN_008ef150 likely constructs an action object)
        iVar3 = FUN_008ef150(&local_10);
        *(undefined4 *)(iVar3 + 8) = 1; // Set some flag

        // Another assertion
        if (pActionListHead == (int *)*(int *)(this + 0x30)) {
            FUN_00b97aea();
        }

        // Look up a resource or string (FUN_00404280)
        local_c = FUN_00404280(pActionListHead[3], _DAT_00e546a0, 0);
        // Send a message or set property (FUN_004035c0) with opcode 0x46
        FUN_004035c0(local_c, 0x46, this);

        // Cleanup action (FUN_008ef250)
        FUN_008ef250(&local_10);
        // Process action list (FUN_008eb890)
        FUN_008eb890(pActionListHead + 4);

        // Iterate over linked list of sub-actions starting at head+4 (offset +0x10)
        pCurrentAction = (undefined4 *)pActionListHead[4];
        for (; pCurrentAction != (undefined4 *)0x0; pCurrentAction = (undefined4 *)*pCurrentAction) {
            iVar3 = pCurrentAction[6]; // offset +0x18: action target ID
            if (iVar3 != 0) {
                // Get object from ID (FUN_004025a0)
                iVar4 = FUN_004025a0(iVar3);
                if ((iVar4 != 0) && (cVar2 = FUN_00402c80(), cVar2 == '\0')) {
                    // Apply action to object (FUN_00406130)
                    FUN_00406130(iVar3, local_c, _DAT_00d80de4);
                }
                // Check if action is still valid (FUN_008ee8b0)
                iVar4 = FUN_008ee8b0(pCurrentAction[6]);
                if (iVar4 == 0) {
                    // Remove action (FUN_004061b0)
                    FUN_004061b0(iVar3);
                }
            }
            pActionListHead = (int *)local_4;
        }

        // Finalize processing (FUN_008edd00)
        FUN_008edd00(local_8, this + 0x2c, pActionListHead);
    }
    return;
}