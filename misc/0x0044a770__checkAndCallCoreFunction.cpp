// FUNC_NAME: checkAndCallCoreFunction
// Address: 0x0044a770
// This function checks a global manager state and conditionally calls the core function.
// If the global manager pointer (g_pManager) is non-null and the byte at offset 0x14 is set,
// it invokes FUN_0044b390 (likely a validation routine). If that returns non-zero, it returns early.
// Otherwise, it proceeds to call the main routine FUN_0044a7c0.

void checkAndCallCoreFunction(void)
{
    char validationResult;
    // Temporary buffer used by FUN_0044b390 (unused result)
    char temporaryBuffer[4];
    int unusedFlag = 0;

    // Check global singleton: must exist and have a specific flag set (offset 0x14)
    // DAT_01223444 is a pointer to a manager/state structure
    if ((g_pManager != 0) && (*(char *)(g_pManager + 0x14) != '\0'))
    {
        unusedFlag = 0;
        // Call validation function with a temporary buffer (output ignored)
        validationResult = FUN_0044b390(temporaryBuffer);
        // If validation passes (non-zero return), skip the core function
        if (validationResult != '\0')
        {
            return;
        }
    }
    // Execute the main logic
    FUN_0044a7c0();
}