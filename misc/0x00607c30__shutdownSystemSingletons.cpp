// FUNC_NAME: shutdownSystemSingletons
void shutdownSystemSingletons() {
    // Shutdown system module 1 (e.g., audio engine)
    if (g_pSystemModule1 != nullptr) {
        // vtable+8: release/destructor method (__thiscall)
        (*(void(__thiscall*)(void*))(*(uint32_t*)g_pSystemModule1 + 8))(g_pSystemModule1);
        g_pSystemModule1 = nullptr;
    }
    // Shutdown system module 2
    if (g_pSystemModule2 != nullptr) {
        (*(void(__thiscall*)(void*))(*(uint32_t*)g_pSystemModule2 + 8))(g_pSystemModule2);
        g_pSystemModule2 = nullptr;
    }
    // Shutdown system module 3
    if (g_pSystemModule3 != nullptr) {
        (*(void(__thiscall*)(void*))(*(uint32_t*)g_pSystemModule3 + 8))(g_pSystemModule3);
        g_pSystemModule3 = nullptr;
    }
}