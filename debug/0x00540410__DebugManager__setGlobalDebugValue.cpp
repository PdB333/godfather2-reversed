// FUNC_NAME: DebugManager::setGlobalDebugValue
void __thiscall DebugManager::setGlobalDebugValue(DebugManager* this, int value)
{
    // +0x28: boolean flag indicating whether debug features are enabled
    if (this->m_debugEnabled)
    {
        // Enable some internal debug mechanism (e.g., logging, profiling)
        FUN_00ab51e0(1);
        // Store the provided value in a global variable (likely used for debug configuration)
        g_debugGlobalValue = value;
    }
}