// FUNC_NAME: SomeManager::tryExecuteAction
// Function address: 0x00634030
// Role: Attempts to execute an action based on current state and input state.
// Returns: 1 on success, 0 on failure (but condition met), -1 on general failure.

int SomeManager::tryExecuteAction(int param_1, int* param_2) {
    int* piVar1;
    int iVar2;
    int* unaff_EDI; // Likely a global or static pointer to current state

    // Check if current state is 5 or 7
    if (((*unaff_EDI == 5) || (*unaff_EDI == 7)) &&
        (piVar1 = (int*)FUN_00637f90(), *piVar1 != 0)) {
        // If input state is also 5 or 7, call FUN_00637f90 again (maybe reset?)
        if ((*param_2 == 5) || (*param_2 == 7)) {
            FUN_00637f90();
        }
        iVar2 = FUN_00636800();
        if (iVar2 != 0) {
            FUN_00633ac0(param_1, piVar1);
            // Check pointer at this+8 (offset 0x8) for some condition
            iVar2 = **(int**)(param_1 + 8);
            if ((iVar2 != 0) && ((iVar2 != 1 || ((*(int**)(param_1 + 8))[1] != 0)))) {
                return 1;
            }
            return 0;
        }
    }
    return -1;
}