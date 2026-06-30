// FUNC_NAME: ForwardToGlobalManager (calls virtual func at 0xCC on global singleton)
void ForwardToGlobalManager(uint32_t param_1)
{
    // Global singleton pointer at 0x01223510
    if (g_globalManager != 0) {
        // Call virtual function at vtable offset 0xCC (index 51) with param_1
        ((void (*)(uint32_t))(*g_globalManager + 0xCC))(param_1);
    }
}