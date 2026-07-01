// FUNC_NAME: registerCoreSystems
// Function address: 0x008f6c80
// Role: Registers three core engine components/systems during startup.
// Calls a helper function (likely registerComponent or initializeSystem) with pointers to static data (strings or objects).
void registerCoreSystems(void)
{
    // Register first component (e.g., "AudioSystem", "RenderSystem", etc.)
    registerComponent((const char*)0x00472420);
    // Register second component
    registerComponent((const char*)0x00472440);
    // Register third component
    registerComponent((const char*)0x007977b0);
    return;
}