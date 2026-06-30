//FUNC_NAME: ShutdownGlobalManager
void ShutdownGlobalManager(void)
{
    // Global pointer to a manager singleton (likely GodfatherGameManager or SimManager)
    // +0x0: vtable pointer, first entry is a virtual function (e.g., release or shutdown)
    if (g_pGlobalManager != nullptr) {
        // Call the first virtual function with argument 1 (shutdown flag)
        (*(void (__thiscall **)(int))(*g_pGlobalManager))(1);
    }
}