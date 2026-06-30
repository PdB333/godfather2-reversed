// FUNC_NAME: engineStartup
// Function address: 0x005ea740
// Role: Part of the EARS engine initialization sequence. Calls two core subsystem initializers.
void engineStartup()
{
    // Subsystem initialization #1 (address 0x00ab4d30) – possibly memory manager or object factory
    initMemoryManager();
    // Subsystem initialization #2 (address 0x00abd5c0) – possibly task scheduler or input system
    initTaskScheduler();
    return;
}