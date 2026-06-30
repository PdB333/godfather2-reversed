// FUNC_NAME: initializeSystem
void initializeSystem(void)
{
    // Initialize base engine core (memory manager, threading, etc.)
    initializeEngineCore();    // 0x00414aa0
    // Initialize subsystem (called twice, possibly for two components or phases)
    initializeSubsystem();     // 0x00417560
    initializeSubsystem();     // 0x00417560
}