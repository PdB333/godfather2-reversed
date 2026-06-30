// FUNC_NAME: processActionWithAllocation
int processActionWithAllocation(int param_1, int param_2, int param_3, undefined4 param_4, undefined4 param_5)
{
    int result;
    int i;
    void* allocatedBuffer;
    int local_30[3]; // offset0, size=0x40, flags
    undefined1 local_20[16];
    undefined1 local_10[16];

    allocatedBuffer = calloc(4, 0x40);
    if (allocatedBuffer == NULL) {
        // Allocation failed — look up error code from a global table
        i = 0;
        while (globalErrorTable[i * 2] != -2) {
            i = i + 1;
            if (2 < i) {
                return 1;
            }
        }
        // Return error code from table
        return *(undefined4 *)(globalErrorTableData + i * 8);
    }

    // Initialize local descriptor
    local_30[0] = 0;
    local_30[1] = 0x40;  // buffer size
    local_30[2] = 0;

    result = FUN_00665ce0();
    if (result == 0) {
        // Check initial condition
        if (local_30[0] != 0) {
            local_30[2] = (*(int *)(param_2 + 0x18) == 0) ? 1 : 0;
        }

        result = FUN_00668850(local_30, param_4);
        if (result == 0) {
            // Sequence of checks — likely multiple successive calls
            int check1 = FUN_00665bd0();
            if (check1 == 0) {
                int check2 = FUN_00665bd0();
                if (check2 == 0 || (check2 = FUN_00665bd0(), check2 == 0)) {
                    // All checks passed
                    FUN_00665b40();  // Some success handler?
                    return FUN_006624a0(param_1, param_3, param_5);
                }
            }

            // Fallback logic
            int cmpResult = FUN_00667820(local_10, local_20, 0);
            if (cmpResult != 0) {
                FUN_00665b40();
                return FUN_0066cf40();  // Error/fallback return
            }

            // Main processing chain
            result = FUN_0066a780(param_1, param_2);
            if (result == 0) {
                // ... many more checks involving math/state machines
                if (FUN_00665c00() == -1 || FUN_006657c0(local_30) == 0) {
                    if (FUN_00667910(param_4, local_30) == 0) {
                        result = FUN_0066a780(param_1 + 0x10, param_2 + 0x10);
                        if (result == 0) {
                            // Another set of conditions
                            if (FUN_00665c00() == -1 || (FUN_006657c0(local_20) == 0 && 
                                FUN_00668ce0(local_20, local_30, local_20) == 0 && 
                                FUN_0066a090(local_20, param_4, param_5) == 0 && 
                                FUN_0066a660(local_20, local_30) == 0)) {
                                if (FUN_0066a090(local_30, param_4, param_5) == 0) {
                                    // Final operations
                                    if (FUN_0066a780(local_30, param_1) == 0 && 
                                        FUN_0066a780(local_30, param_2) == 0 && 
                                        FUN_0066a780(param_1, local_10) == 0 && 
                                        FUN_00668ce0(local_30, local_20, local_30) == 0 && 
                                        FUN_0066a8d0(local_30, param_1 + 0x10, param_4, param_3 + 0x10) == 0 && 
                                        FUN_00668850(local_10, param_4) == 0) {
                                        return 0; // Success
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // Error path
            result = FUN_0066cf40();  // Maybe an error function
            FUN_00665b80(local_20, local_10, local_30, 0); // Cleanup
            return result;
        }
    }

    // Fallthrough error
    FUN_00665b40();
    i = 0;
    while (result != globalErrorTable[i * 2]) {
        i = i + 1;
        if (2 < i) {
            return 1;
        }
    }
    return *(undefined4 *)(globalErrorTableData + i * 8);
}