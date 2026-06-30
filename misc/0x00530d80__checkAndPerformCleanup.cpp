//FUNC_NAME: checkAndPerformCleanup
// Function at 0x00530d80: Checks if two global counters match, then cleans up two resources if they exist.
void checkAndPerformCleanup(void)
{
    // Compare two global counters (likely reference counts or state IDs)
    if (g_cleanupCounter1 == g_cleanupCounter2) {
        // If first resource pointer is non-null, release it
        if (g_resourcePtr1 != 0) {
            cleanupResource(); // Calls resource cleanup routine (FUN_006063b0)
        }
        // If second resource pointer is non-null, release it
        if (g_resourcePtr2 != 0) {
            cleanupResource(); // Calls resource cleanup routine (FUN_006063b0)
        }
    }
}