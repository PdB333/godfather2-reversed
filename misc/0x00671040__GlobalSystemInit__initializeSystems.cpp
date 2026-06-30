// FUNC_NAME: GlobalSystemInit::initializeSystems
void __fastcall initializeSystems(uint32_t systemHandle)
{
    // Store the provided handle into the global system manager handle
    g_systemManagerHandle = systemHandle;

    // Retrieve and store three subsystem components (likely singletons or factory-created objects)
    g_subSystemComponent1 = createOrGetSubsystemComponent();
    g_subSystemComponent2 = createOrGetSubsystemComponent();
    g_subSystemComponent3 = createOrGetSubsystemComponent();

    // Reset various global flags/states
    g_isInitialized = 0;        // +0x12058ba (bool/byte)
    g_subsystemReadyFlag1 = 0; // +0x12066ac (bool)
    g_subsystemReadyFlag2 = 0; // +0x12066ad (bool)
}