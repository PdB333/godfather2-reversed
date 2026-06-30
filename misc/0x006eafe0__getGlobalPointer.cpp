// FUNC_NAME: getGlobalPointer
undefined4* getGlobalPointer(int bEnabled)
{
    undefined4* result;
    
    if (bEnabled != 0) {
        result = GetInstanceFromGlobal(g_pGlobalManager); // FUN_0043b870
        return result;
    }
    return 0;
}