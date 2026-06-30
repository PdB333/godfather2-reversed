// FUNC_NAME: DebugSymbolManager::initDbgHelp
void DebugSymbolManager::initDbgHelp(void)
{
    HMODULE hModule;
    FARPROC pFVar1;
    int *unaff_ESI; // this pointer (DebugSymbolManager instance)
    
    if (*unaff_ESI == 0) {
        hModule = LoadLibraryA("DbgHelp.dll");
        *unaff_ESI = (int)hModule;
        if (hModule != (HMODULE)0x0) {
            // +0x08: SymInitialize function pointer
            pFVar1 = GetProcAddress(hModule, "SymInitialize");
            unaff_ESI[2] = (int)pFVar1;
            // +0x0C: SymCleanup function pointer
            pFVar1 = GetProcAddress((HMODULE)*unaff_ESI, "SymCleanup");
            unaff_ESI[3] = (int)pFVar1;
            // +0x10: StackWalk function pointer
            pFVar1 = GetProcAddress((HMODULE)*unaff_ESI, "StackWalk");
            unaff_ESI[4] = (int)pFVar1;
            // +0x14: SymFunctionTableAccess function pointer
            pFVar1 = GetProcAddress((HMODULE)*unaff_ESI, "SymFunctionTableAccess");
            unaff_ESI[5] = (int)pFVar1;
            // +0x18: SymGetModuleBase function pointer
            pFVar1 = GetProcAddress((HMODULE)*unaff_ESI, "SymGetModuleBase");
            unaff_ESI[6] = (int)pFVar1;
            // +0x1C: SymGetSymFromAddr function pointer
            pFVar1 = GetProcAddress((HMODULE)*unaff_ESI, "SymGetSymFromAddr");
            unaff_ESI[7] = (int)pFVar1;
            // +0x20: SymGetLineFromAddr function pointer
            pFVar1 = GetProcAddress((HMODULE)*unaff_ESI, "SymGetLineFromAddr");
            unaff_ESI[8] = (int)pFVar1;
        }
    }
    return;
}