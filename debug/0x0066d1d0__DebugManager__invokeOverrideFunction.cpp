// FUNC_NAME: DebugManager::invokeOverrideFunction

void __thiscall DebugManager::invokeOverrideFunction(void *param_2, void *param_3)
{
    // g_pOverrideFunc: global hook function pointer (DAT_0120668c)
    // If installhook has replaced this function, call the override
    if (g_pOverrideFunc == 0) {
        char result;
        void *pDebugAllocator = 0;

        // vtable+0x10: virtual method to obtain a debug allocator by hash (e.g., 0x4f3368d0)
        result = (*(char (__thiscall **)(unsigned int, void **))(*(int *)this + 0x10))(0x4f3368d0, &pDebugAllocator);

        // g_pDebugManager is a global (unaff_EBP) pointing to the debug system instance
        if (result && g_pDebugManager) {
            int *pManagerObj = *(int **)((char *)g_pDebugManager + 0x260); // +0x260: manager object pointer
            if (pManagerObj) {
                // FUN_009f2000: debug system initialization/lock (e.g., DebugSync)
                DebugSync();
                // pManagerObj+0xd0 points to a vtable, call method at index (0x48/4)=0x12
                (*(void (__thiscall **)(void *))(*(int *)((char *)pManagerObj + 0xd0) + 0x48))(param_2);
            }
            pManagerObj = *(int **)((char *)g_pDebugManager + 0x260);
            if (pManagerObj) {
                DebugSync();
                // vtable method at index (0x50/4)=0x14
                (*(void (__thiscall **)(void *))(*(int *)((char *)pManagerObj + 0xd0) + 0x50))(param_3);
            }
        }
        return;
    }
    // Redirect to the installed hook
    g_pOverrideFunc(this, param_2, param_3);
}