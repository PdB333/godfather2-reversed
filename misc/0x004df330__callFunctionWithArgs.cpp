// FUNC_NAME: callFunctionWithArgs
undefined4 __cdecl callFunctionWithArgs(undefined4 param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4* param_8)
{
    undefined4 local_30;
    undefined4 local_2c;
    undefined4 local_28;
    undefined4 local_24;
    undefined4 local_20;
    undefined4 local_1c;
    undefined4 local_18;
    uint local_14;

    // If param_8 is non-null, copy the first 3 words into local variables and set the 4th from a global
    if (param_8 != (undefined4 *)0x0) {
        local_30 = *param_8;
        local_2c = param_8[1];
        local_28 = param_8[2];
        local_24 = DAT_00e2b1a4;  // global constant or state?
    }

    // Set up argument block:
    // local_20 acts as a type/count indicator (value 2)
    // local_1c and local_18 pass param_6 and param_7 through
    // local_14 is a pointer to the copied data (or null if param_8 was null)
    local_1c = param_6;
    local_14 = -(uint)(param_8 != (undefined4 *)0x0) & (uint)&local_30; // conditional pointer to copied data
    local_18 = param_7;
    local_20 = 2;

    // Call the actual dispatch function with the constructed argument block
    FUN_004df270(param_1, param_2, param_3, param_4, param_5, &local_20);
    return param_1;
}