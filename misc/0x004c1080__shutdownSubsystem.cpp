// FUNC_NAME: shutdownSubsystem
// Address: 0x004c1080
// Purpose: Sequentially cleans up two subsystems (likely identical managers or objects)
// and then performs a global shutdown routine. Called during game exit from FUN_004c1550.
void shutdownSubsystem(void)
{
    // Cleanup first subsystem (e.g., input manager or network layer)
    FUN_004c2390();
    // Cleanup second subsystem (same pattern, possibly another instance)
    FUN_004c2390();
    // Global engine shutdown (e.g., deinitialize EARS core)
    FUN_009c8eb0();
    return;
}