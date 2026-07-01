// FUNC_NAME: ApplicationShutdown
// Function address: 0x00927400
// Role: Shuts down the global memory pool and invokes engine finalization.
void ApplicationShutdown(void)
{
    bool bPoolActive;
    
    bPoolActive = (bool)FUN_00402080(&g_mainMemoryPool); // Check if memory pool is active
    if (bPoolActive) {
        FUN_004086d0(&g_mainMemoryPool); // Free/shutdown the memory pool
    }
    FUN_005c1820(); // Perform engine-wide finalization
    return;
}