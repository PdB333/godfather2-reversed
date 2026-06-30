// FUNC_NAME: sendTwoCommands
void sendTwoCommands(undefined2 **param_1) // param_1 likely a pointer to a struct with two pointer fields (e.g., command buffer)
{
    undefined2 *cmd1;
    undefined2 *cmd2;
    undefined2 *local_28; // temporary pointer
    undefined4 local_24;  // argument for processData
    code *local_1c;       // function pointer for cleanup
    int local_18;         // another temporary
    undefined4 local_14;  // argument for second sendCommand
    code *local_c;        // function pointer for cleanup

    // Allocate two 4-byte command structures (each holds two 16-bit values)
    cmd1 = (undefined2 *)FUN_009c8e50(4); // allocate(4)
    *cmd1 = 0x1e;   // command ID 0x1e
    cmd1[1] = 0;    // parameter

    cmd2 = (undefined2 *)FUN_009c8e50(4); // allocate(4)
    *cmd2 = 0x1f;   // command ID 0x1f
    cmd2[1] = 0;    // parameter

    // Send first command: (data, size, arg1, arg2) – arg1/arg2 from param_1
    FUN_004dbf70(cmd1, 1, *param_1, param_1[1]);

    // Second sendCommand – arguments likely misordered by decompiler;
    // probably intended as (cmd2, 1, local_18, local_14) but local_18/local_14 are uninitialized.
    // Possibly they are the same as *param_1 and param_1[1]? Or set by first call?
    FUN_004dbf70(local_18, local_14, cmd2, 1); // Suspect: should be (cmd2, 1, local_18, local_14)

    // Conditional processing based on param_1 vs local_28 address
    if (param_1 != &local_28) {
        undefined2 *ptr = local_28;
        if (ptr == (undefined2 *)0x0) {
            ptr = &DAT_00e2df14; // default data pointer
        }
        FUN_004dbb10(ptr, 0, local_24); // processData(ptr, 0, local_24)
    }

    // Cleanup of temporary pointers
    if (local_28 != (undefined2 *)0x0) {
        (*local_1c)(local_28); // call destructor/free via function pointer
    }
    if (local_18 != 0) {
        (*local_c)(local_18); // call destructor/free via function pointer
    }

    // Free allocated command structures
    thunk_FUN_009c8eb0(cmd2); // deallocate
    thunk_FUN_009c8eb0(cmd1); // deallocate

    return;
}