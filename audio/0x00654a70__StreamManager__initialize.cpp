// FUNC_NAME: StreamManager::initialize
void StreamManager::initialize(void* context)
{
    static bool initialized = false;
    if (!initialized)
    {
        initialized = true;
        StreamManager_construct(&g_streamManager);  // FUN_00662100
        StreamManager_init(&g_streamManager);       // FUN_006622a0
    }
    StreamManager_addStream(context, 8, &g_streamManager);  // FUN_00662350
}