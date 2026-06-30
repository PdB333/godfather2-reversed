// FUNC_NAME: ResourceManager::releaseHandle
void __fastcall ResourceManager::releaseHandle(uint32* thisPtr)
{
    int32 handleIndex = thisPtr[2]; // +0x08 - handle index or reference count, -1 means invalid/unused

    if (handleIndex >= 0) {
        // Get thread-local storage pointer for the resource manager instance
        void* tlsValue = TlsGetValue(DAT_01139810); // TLS index for per-thread manager

        // Call internal release function: first field at +0x00 is resource ID,
        // handleIndex << 4 is byte offset into an allocation table, 0x17 is a resource type constant
        FUN_00aa26e0(thisPtr[0], handleIndex << 4, 0x17);
    }
}