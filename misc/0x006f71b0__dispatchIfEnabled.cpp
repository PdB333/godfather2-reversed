// FUNC_NAME: dispatchIfEnabled
uint dispatchIfEnabled(uint param1, uint param2)
{
    // in_EAX holds the value of the EAX register at function entry.
    // This value is typically the return value from a previous call
    // or a status code that may need to be preserved/modified.
    uint eax;
    // Reconstructing the register read: eax = (uint)__readeflags()? Not exact.
    // For analysis, we treat it as an implicit parameter.
    uint result = eax & 0xFFFFFF00; // Preserve high 24 bits, clear low byte
    if (g_bEnableFeature != 0)      // Global toggle at 0x0112aa10
    {
        result = delegateFunction(param1, param2); // FUN_006f6ef0
    }
    return result;
}