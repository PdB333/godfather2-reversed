// FUNC_NAME: DebugHelpManager::initDbgHelp
void __thiscall DebugHelpManager::initDbgHelp(void)
{
    // this pointer in ESI, offsets documented below
    if (this->m_hDbgHelp == 0) // +0x00
    {
        this->m_hDbgHelp = LoadLibraryA("DbgHelp.dll"); // +0x00
        if (this->m_hDbgHelp != 0)
        {
            // +0x08: pfnSymInitialize
            this->m_pfnSymInitialize = GetProcAddress(this->m_hDbgHelp, "SymInitialize");
            // +0x0C: pfnSymCleanup
            this->m_pfnSymCleanup = GetProcAddress(this->m_hDbgHelp, "SymCleanup");
            // +0x10: pfnStackWalk
            this->m_pfnStackWalk = GetProcAddress(this->m_hDbgHelp, "StackWalk");
            // +0x14: pfnSymFunctionTableAccess
            this->m_pfnSymFunctionTableAccess = GetProcAddress(this->m_hDbgHelp, "SymFunctionTableAccess");
            // +0x18: pfnSymGetModuleBase
            this->m_pfnSymGetModuleBase = GetProcAddress(this->m_hDbgHelp, "SymGetModuleBase");
            // +0x1C: pfnSymGetSymFromAddr
            this->m_pfnSymGetSymFromAddr = GetProcAddress(this->m_hDbgHelp, "SymGetSymFromAddr");
            // +0x20: pfnSymGetLineFromAddr
            this->m_pfnSymGetLineFromAddr = GetProcAddress(this->m_hDbgHelp, "SymGetLineFromAddr");
        }
    }
}