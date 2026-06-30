// FUNC_NAME: SimManager::getInstanceIfAvailable
// Function at 0x006bea40: Conditional accessor for the global SimManager instance.
// Returns the SimManager instance if param_1 (requireInstance) is true, otherwise 0.
// Callee 0x0043b870 retrieves the actual instance pointer from the singleton pointer (DAT_01131018).

bool SimManager::getInstanceIfAvailable(bool requireInstance)
{
    if (requireInstance) {
        // Retrieve the global SimManager instance from the singleton pointer.
        SimManager* instance = getSimManagerFromGlobal(DAT_01131018);
        return instance;
    }
    return 0;
}