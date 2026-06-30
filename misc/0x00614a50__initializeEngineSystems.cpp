// FUNC_NAME: initializeEngineSystems
void initializeEngineSystems(void)
{
    // Initialize two global objects, likely a manager and its configuration block
    initObjectPair(&g_ManagerSingleton, &g_ManagerConfig); // 0x006131d0: placement new or multi-arg init
    // Initialize memory/heap subsystem
    initMemoryManager(); // 0x00417560
    // Initialize the streaming system (e.g., asset loading)
    initStreamingSystem(); // 0x00611f70
    // Initialize the audio subsystem
    initAudioSystem(); // 0x00612130
    // Initialize the networking component with a global data block
    initNetworkComponent(&g_NetworkComponent); // 0x00612210
}