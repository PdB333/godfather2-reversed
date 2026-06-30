// FUNC_NAME: 0x004b12a0 - LogManager::writeEntry

// +0x00: const char* pData  // pointer to log data buffer
// +0x04: int unused         // not used in this function
// +0x08: int nIndex         // index into log entries (offset = nIndex << 4)
void __thiscall LogManager::writeEntry(LogManager* thisPtr)
{
    int nIndex = thisPtr->nIndex;
    if (nIndex >= 0)
    {
        // Retrieve thread-specific log buffer via TLS
        void* pThreadData = TlsGetValue(g_TLSIndex);
        // Write 16 bytes of data with log type 0x17 (23 = debug/info?)
        FUN_00aa26e0(thisPtr->pData, nIndex << 4, 0x17);
    }
}