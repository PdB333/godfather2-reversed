// FUNC_NAME: Thunk::callViaGlobalTable
// Function address: 0x00559dc0
// This function is a dispatch thunk that calls a function pointer from a global table.
// It takes four parameters but only three are forwarded; the fourth (unusedArg) is ignored.

void Thunk::callViaGlobalTable(void* arg1, void* arg2, void* arg3, int unusedArg) {
    // Store unused parameter (likely for stack cleanup or alignment)
    int unused = unusedArg;
    char padding = 0; // Possibly stack alignment padding

    // Global pointer to a function pointer table
    // PTR_LAB_00dcf98c is a pointer to a struct of function pointers (table)
    void*** tablePtr = (void***)&PTR_LAB_00dcf98c; // Address of the global pointer variable

    // Dispatch to the function in the table
    // Parameters are passed in a specific order: arg2, arg1, arg3, and the table pointer address
    FUN_00c0a110(arg2, arg1, arg3, tablePtr);
}