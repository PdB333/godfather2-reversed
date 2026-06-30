// FUNC_NAME: initializeGlobalContext

void initializeGlobalContext(void)
{
    // Check if the global context pointer is not yet initialized
    if (g_pGlobalContext == nullptr) {
        // Initialize to point to the static global context structure
        g_pGlobalContext = &g_globalContextBuffer;
    }
}