// FUNC_NAME: shutdownEngineSystems
void shutdownEngineSystems(void)
{
    // Set engine shutdown state to 2 (shutting down)
    g_engineShutdownState = 2;

    // Shutdown subsystem 1 (e.g., audio manager)
    if (g_pAudioManager != nullptr) {
        (*(code**)*g_pAudioManager)(1); // Virtual call at offset 0 (release/shutdown)
    }

    // Shutdown subsystem 2 (e.g., input manager)
    if (g_pInputManager != nullptr) {
        (*(code**)*g_pInputManager)(1);
    }

    // Shutdown subsystem 3 (e.g., stream manager)
    if (g_pStreamManager != nullptr) {
        (*(code**)*g_pStreamManager)(1);
    }

    // Call internal shutdown function (likely for common subsystems)
    internalShutdownFunction(); // 0x004dfff0

    // Shutdown subsystem 4 (e.g., render manager)
    if (g_pRenderManager != nullptr) {
        (*(code**)*g_pRenderManager)(1);
    }

    // Deallocate resource pool A
    if (g_pResourcePoolA != nullptr) {
        // Release the resource object and free its container
        releaseResourceObject(*g_pResourcePoolA);   // 0x009c8f10
        freeResourceContainer(g_pResourcePoolA);    // 0x009c8eb0
        g_pResourcePoolA = nullptr;
    }

    // Deallocate resource pool B
    if (g_pResourcePoolB != nullptr) {
        // Release the resource object and free its container
        releaseResourceObject(*g_pResourcePoolB);   // 0x009c8f10
        freeResourceContainer(g_pResourcePoolB);    // 0x009c8eb0
        g_pResourcePoolB = nullptr;
    }

    // Deallocate resource pool C (note: different structure: check pointer value first)
    if (g_pResourcePoolC != nullptr) {
        if (*g_pResourcePoolC != 0) {
            releaseResourceObject(*g_pResourcePoolC); // 0x009c8f10
        }
        freeResourceContainer(g_pResourcePoolC); // 0x009c8eb0
        g_pResourcePoolC = nullptr;
    }

    // Reset engine state to idle
    g_engineShutdownState = 0;

    // Call finalization on the main engine object (vtable offset 0xC)
    (*(code**)(*g_pEngineObject + 0xC))();

    // Clear main engine pointer
    g_pEngineObject = nullptr;
}