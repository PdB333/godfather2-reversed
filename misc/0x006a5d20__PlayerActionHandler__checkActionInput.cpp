// FUNC_NAME: PlayerActionHandler::checkActionInput
void __thiscall PlayerActionHandler::checkActionInput(int thisPtr) {
    char local_5;
    int iVar2;
    int local_4;

    // +0x68c: actionMode (0 = normal, 0x48 = cover?)
    int actionMode = *(int *)(thisPtr + 0x68c);
    // +0x67c..0x688: array of 4 action flags (e.g., button states)
    int *actionFlags = (int *)(thisPtr + 0x67c);

    // Only process if mode is normal or cover, and at least one flag is set
    if ((actionMode == 0 || actionMode == 0x48) &&
        (actionFlags[0] != 0 || actionFlags[1] != 0 || actionFlags[2] != 0 || actionFlags[3] != 0)) {
        local_5 = 0;
        // Map flags to an action ID (e.g., via a lookup table)
        iVar2 = FUN_00448100(actionFlags, &local_5);
        if (iVar2 != 0) {
            local_4 = 0;
            // Check if the action ID matches the hash for "use" (0x2e5f1298)
            char cVar1 = FUN_006a4e80(iVar2, 0x2e5f1298, &local_4);
            if (cVar1 != '\0') {
                // Execute the matched action
                FUN_006a4e40(local_4);
                // Global update (e.g., clear input state)
                FUN_006a6980();
            }
        }
    }
}