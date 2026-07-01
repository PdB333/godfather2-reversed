// FUNC_NAME: engineSubsystemInitialize
void engineSubsystemInitialize(void)
{
    // Call the actual initialization routine
    FUN_008c3520();

    // Register a cleanup handler for the global engine subsystem data
    // This likely calls atexit or a similar mechanism to ensure cleanup on shutdown
    FUN_00408680(&DAT_012069c4);
}