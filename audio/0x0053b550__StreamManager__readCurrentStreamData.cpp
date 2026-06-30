// FUNC_NAME: StreamManager::readCurrentStreamData

void StreamManager::readCurrentStreamData() {
    // Global array of stream entries (size 0x38 each)
    // g_streamArray is at DAT_0112540c, g_streamIndex is at DAT_01125388
    // g_globalPtr is at DAT_011252e8 (likely singleton manager reference)
    StreamEntry* entry = &g_streamArray[g_streamIndex]; // +0x00: data pointer

    if (entry->dataPtr != nullptr) {
        int unused1 = 0;
        int unused2 = 0;
        int unused3 = 0;
        // Buffer to receive read result (4 bytes)
        int buffer;
        // Read data from the stream entry into buffer
        readStreamData(g_globalPtr, entry->dataPtr, &buffer);
    }
}