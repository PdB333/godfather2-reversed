// FUNC_NAME: cleanupManager
void cleanupManager(void)
{
    int i;
    
    // Clean up the primary manager object
    sub_004d4300(&g_primaryManager);
    
    // Iterate through all secondary manager instances and clean each one
    i = 0;
    if (0 < g_secondaryManagerCount) {
        do {
            sub_004d4300(&g_secondaryManagerInstance);
            i = i + 1;
        } while (i < g_secondaryManagerCount);
    }
    return;
}