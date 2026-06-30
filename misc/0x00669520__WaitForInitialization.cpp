// FUNC_NAME: WaitForInitialization
int WaitForInitialization(int* pStatus)
{
    int result;
    uint* pTimer;

    *pStatus = 0;                                  // Reset status flag
    pTimer = reinterpret_cast<uint*>(0x00e275c0);  // Base address of timer region

    while (true)
    {
        result = CheckInitializationDone();        // Check if hardware is ready
        if (result != 0)                           // If ready, return success
        {
            return result;
        }

        if (pStatus == nullptr)                    // Safety check for null pointer
            break;

        pTimer++;                                  // Increment timer pointer
        if (reinterpret_cast<uint32_t>(pTimer) > 0x00e279bf) // Timeout after 256 iterations? (0x3FF / 4 = 256)
        {
            return 0;                              // Return 0 on timeout
        }
    }

    // Note: The following line appears to be a decompiler artifact (writing to address 0).
    // In original code, this might have been a global flag write, e.g., g_initializationDone = 1;
    // uRam00000000 = 1; 
    *(volatile uint32_t*)0 = 1;                    // Placeholder for hardware write

    return 0;
}