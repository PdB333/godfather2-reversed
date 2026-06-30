// FUNC_NAME: initializeGlobalConfig
void __cdecl initializeGlobalConfig(uint param_1, uint param_2, uint param_3, uint param_4)
{
    // Calls an initialization or setup routine (likely allocates or initializes some internal state)
    FUN_00557e20();

    // Store param_4 – possibly unused in this function, or used later via a global pointer
    uint local_4 = param_4;

    // Load a global data pointer (address: 0x00e445dc)
    uint globalData = DAT_00e445dc;

    // Retrieve a pointer to a global table of function pointers or data (PTR_LAB_00dcf974)
    undefined **tablePtr = (undefined**)&PTR_LAB_00dcf974;

    // Call a core function with parameters rearranged and a reference to the table pointer.
    // The third argument (param_1) is moved to the first position, param_2 to second,
    // param_3 to third, and &tablePtr as the last argument.
    FUN_00c09cc0(param_2, param_1, param_3, (undefined*)&tablePtr);
}