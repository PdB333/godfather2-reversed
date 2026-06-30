// FUNC_NAME: shutdownGameSystems
void shutdownGameSystems()
{
    // Unregister the main callback (maybe shutdown hook)
    unregisterCallback(0, reinterpret_cast<void*>(0x00413090)); // LAB_00413090 is a function/vtable address

    g_bSomeFlag = false; // DAT_01205322 = 0;

    // Release each global object (likely singletons or managers)
    if (g_pObject0 != nullptr) {
        releaseObject(g_pObject0, 0); // FUN_006065a0(obj, 0)
    }
    g_pObject0 = nullptr;

    if (g_pObject1 != nullptr) {
        releaseObject(g_pObject1, 0);
    }
    g_pObject1 = nullptr;

    if (g_pObject2 != nullptr) {
        releaseObject(g_pObject2, 0);
    }
    g_pObject2 = nullptr;

    if (g_pObject3 != nullptr) {
        releaseObject(g_pObject3, 0);
    }
    g_pObject3 = nullptr;

    if (g_pObject4 != nullptr) {
        releaseObject(g_pObject4, 0);
    }
    g_pObject4 = nullptr;

    if (g_pObject5 != nullptr) {
        releaseObject(g_pObject5, 0);
    }
    g_pObject5 = nullptr;

    // Finalize any remaining subsystems
    finalizeShutdown(); // FUN_004226c0
}