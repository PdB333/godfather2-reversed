// FUNC_NAME: StreamManager::SetSource
void __thiscall StreamManager::SetSource(void* this, void* pSource) {
    // Only proceed if source is valid
    if (pSource == nullptr) {
        return;
    }

    // Temporary buffer for debug/name string (2048 bytes)
    char buffer[2048];
    memset(buffer, 0, sizeof(buffer));

    // Retrieve string representation from source (e.g., filename or debug label)
    // Call virtual function at vtable+0x74 (likely "GetDebugString" or "GetName")
    ((void (__thiscall*)(void*, char*, int))(*((int**)pSource) + 0x1D))(pSource, buffer, 2048);

    // Store source pointer at offset +0x0C (this[3])
    *((int*)this + 3) = (int)pSource;

    // Notify source to start loading/preparation (argument 1 might indicate async flag)
    ((void (__thiscall*)(void*, int))(*((int**)pSource) + 0x1D))(pSource, 1);

    // Check if source is ready (virtual at vtable+0x8C)
    char isReady = ((char (__thiscall*)(void*))(*((int**)pSource) + 0x23))(pSource);
    if (isReady != 0) {
        // If source is ready, clear this object's dirty flag (virtual at vtable+0x68)
        ((void (__thiscall*)(void*, int))(*((int**)this) + 0x1A))(this, 0);
    }
}