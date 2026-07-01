// FUNC_NAME: DelayedResourceLoader::checkAndLoad
void __fastcall DelayedResourceLoader::checkAndLoad(CUnknownClass* this) {
    // +0x1c0: signed flag (negative = pending, positive = done), +0x114: timestamp (ms), +0xf8: resource handle
    // Global time variable at 0x01205224, global hash key constant at 0x0112ad8c (used for string construction)
    uint32_t resourceHash = 0x19fe0b5f; // some predefined hash for a resource
    // Pre-update call (maybe frame hook)
    FUN_00859c50();
    if (*(int32_t*)((uint32_t)this + 0x1c0) < 0) {
        // Clear the pending flag
        *(uint32_t*)((uint32_t)this + 0x1c0) &= 0x7fffffff;
        if (*(uint32_t*)((uint32_t)this + 0x114) + 2000U < g_currentTime) {
            // Timer expired: update timestamp and request resource
            *(uint32_t*)((uint32_t)this + 0x114) = g_currentTime;
            FUN_006ada80(*(void**)((uint32_t)this + 0xf8), resourceHash);
            // Construct a temporary string from global hash key
            uint32_t tempKey = g_hashKey; // DAT_0112ad8c
            byte* bufferPtr = (byte*)stackBuffer; // local_24[8]
            *bufferPtr = 0; // local_28?
            // Call a function that initializes a string structure from the hash key
            // The structure starts with tempKey (pointer?), then buffer pointer, then byte, then buffer
            struct TempString {
                uint32_t keyOrPtr;       // +0x00: local_30
                byte* bufferStart;       // +0x04: local_2c (points to buffer[0])
                byte terminator;         // +0x08: local_28
                byte buffer[8];          // +0x09: local_24[8]
            } tempStr;
            tempStr.keyOrPtr = tempKey;
            tempStr.bufferStart = (byte*)&tempStr.buffer;
            tempStr.terminator = 0;
            // Clear the rest? The local_1c array follows immediately after buffer (offset +0x11)
            // But we treat it as a separate array for the result check.
            int result[7]; // local_1c
            FUN_00408a00(&tempStr, 0);
            if (result[0] != 0) {
                FUN_004daf90(result);
            }
        }
    }
    return;
}