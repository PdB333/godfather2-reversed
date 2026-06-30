// FUNC_NAME: MissionObjective::activate
uint32_t MissionObjective::activate(char* param_1) // this = param_1
{
    int32_t iVar1;
    int32_t iVar2;
    double local_50, local_48;
    char* local_38;
    char* local_30;
    uint32_t local_20, local_18;

    // Global pointer to GameManager or MissionManager (DAT_01223510)
    iVar2 = g_gameManager; // +0x0

    // Check if objective index (param_1+0x9c) is valid by looking up a table at gameManager+0x81c4
    if (*(int32_t*)(*(int32_t*)(param_1 + 0x9c) * 0x10 + 0x81c4 + iVar2) != 0) {
        // Get scripting manager
        iVar3 = FUN_005e9d10(); // probably getScriptManager()
        iVar1 = *(int32_t*)(iVar2 + 0x580); // +0x580: some object pointer (maybe script context)

        if ((iVar1 != 0) && (*param_1 != '\0')) { // check name is non-empty
            // Push a double value onto script stack
            FUN_00c9cbe0(iVar1, *(uint32_t*)(iVar3 + 0x10), 5, &local_50);
            local_48 = (double)*(int32_t*)(param_1 + 0x104); // +0x104: some int converted to double
            local_30 = param_1 + 0x10c; // +0x10c: pointer to a string (name/description)
            local_18 = 0;
            if (*(int32_t*)(param_1 + 0x104) < 0) {
                local_48 = local_48 + _DAT_00e44708; // global double constant
            }
            local_38 = param_1; // this pointer
            local_20 = 0x2ea8fb98; // Fletcher32 hash of "activateObjective" or similar

            // Begin script function call (hash in local_20)
            FUN_00c9eac0(); // startCall()

            local_50 = *(double*)(param_1 + 0x80); // +0x80: some custom value
            // Compare with global constant, if less than delta, set to 0
            if (local_50 - DAT_00e2af60 < *(double*)(*(int32_t*)(iVar2 + 0x580) + 8)) {
                local_50 = 0.0;
            }
            // Push float value with type 5 (float)
            FUN_00c9cd40(5, &local_50);
            // End script function call and execute
            FUN_00c9eae0(); // endCall()

            *(uint32_t*)(param_1 + 0x134) = local_18; // +0x134: set some flag to 0
            return 1;
        }
    }
    return 0;
}