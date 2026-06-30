// FUNC_NAME: performInitWithZero
// Address: 0x00722220
// This function initializes a local integer to zero and passes its address to the initialization routine at 0x00721e50.
// It is used by multiple callers (0x006e9830, 0x00718480, 0x0077bef0) as a common starting point for some process.
void performInitWithZero(void)
{
    int zeroValue = 0; // local variable set to zero
    FUN_00721e50(&zeroValue); // call underlying initialization function with pointer to zero
}