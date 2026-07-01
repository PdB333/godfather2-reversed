// FUNC_NAME: ensureSystemInitialized
void ensureSystemInitialized(void)
{
    // Check if the system singleton already exists (size 0x1c = 28 bytes)
    if (allocateOrGetSingleton(0x1c) != 0) {
        // If not, initialize it
        initializeSystem();
    }
}