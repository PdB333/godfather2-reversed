// FUNC_NAME: Engine::setupPreloadContext
void Engine::setupPreloadContext()
{
    // Stack-allocated structure for preload configuration
    struct PreloadContext {
        void* pData;   // +0x00
        int32_t flags; // +0x04
        int8_t pad;    // +0x08
    } context;

    context.pData = (void*)DAT_0112a640; // Global preload data pointer
    context.flags = 0;
    context.pad = 0;

    FUN_00408a00(&context, 0); // Initialize subsystem with default context
}