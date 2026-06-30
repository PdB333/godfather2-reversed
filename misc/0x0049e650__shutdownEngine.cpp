// FUNC_NAME: shutdownEngine
// Address: 0x0049e650
// Role: Shuts down the engine by resetting a global initialization flag and calling a virtual method on the engine instance.

extern int g_engineInitialized; // 0x0120546c
extern void* g_engineInstance;  // 0x012058e8

void shutdownEngine()
{
    g_engineInitialized = 0;

    if (g_engineInstance != nullptr)
    {
        // Call virtual function at vtable offset 0x20 (slot 8)
        // This is likely a destruction or cleanup routine for the engine object.
        // The function pointer is obtained from the vtable of the object pointed to by g_engineInstance.
        void (*virtualFunc)(void*) = *reinterpret_cast<void(**)(void*)>(
            *reinterpret_cast<void***>(g_engineInstance) + (0x20 / sizeof(void*))
        );
        virtualFunc(g_engineInstance);
    }
}