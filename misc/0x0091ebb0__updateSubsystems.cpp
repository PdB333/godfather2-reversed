// FUNC_NAME: updateSubsystems
void updateSubsystems(void)
{
    // Check if subsystem 1 is active and update it
    if (g_subsystem1Active != 0) {
        updateSubsystem1();
    }
    // Check if subsystem 2 is active and update it, then return
    if (g_subsystem2Active != 0) {
        updateSubsystem2();
        return;
    }
    // If neither active, do nothing
    return;
}