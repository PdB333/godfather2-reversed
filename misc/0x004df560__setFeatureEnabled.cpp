// FUNC_NAME: setFeatureEnabled
// Function address: 0x004df560
// Role: Calls a subsystem initializer with a enable/disable flag (1 = enable)

void setFeatureEnabled(void)
{
    // Calls the target function at 0x0051aa50, which likely sets a global flag
    // or initializes a subsystem. Parameter 1 presumably enables the feature.
    FUN_0051aa50(1);
    return;
}