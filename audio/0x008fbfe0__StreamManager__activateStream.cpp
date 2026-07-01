// FUNC_NAME: StreamManager::activateStream
void __fastcall StreamManager::activateStream(StreamManager* thisPtr)
{
    // Set the active flag at offset 0xC8 (200 in decimal)
    *(uint8_t*)((uintptr_t)thisPtr + 0xC8) = 1;

    // If a global resource is already loaded, copy its data into our buffer
    if (g_globalResource != 0) {
        copyData((void*)((uintptr_t)thisPtr + 0x3C), &g_globalResource, 0x8000);
    }

    // Check current GUID (four ints at offsets 0xCC, 0xD0, 0xD4, 0xD8)
    int* guid = (int*)((uintptr_t)thisPtr + 0xCC);
    // The magic invalid GUID constants
    const int kInvalidGuid0 = -0x45245246;  // 0xBABDBDBA
    const int kInvalidGuid1 = -0x41104111;  // 0xBEEFBEEF
    const int kInvalidGuid2 = -0x153EA5AB;  // 0xEAC15A55
    const int kInvalidGuid3 = -0x6EEFF6EF;  // 0x91100911

    // Check if the current GUID is either the invalid magic or all zeros
    bool isInvalidOrZero = (guid[0] == kInvalidGuid0 && guid[1] == kInvalidGuid1 && guid[2] == kInvalidGuid2 && guid[3] == kInvalidGuid3) ||
                           (guid[0] == 0 && guid[1] == 0 && guid[2] == 0 && guid[3] == 0);

    if (!isInvalidOrZero) {
        // GUID has a valid asset reference: reset it and notify
        clearGuid(guid, 0);
        notifyAssetReset(0);
        return;
    }

    // GUID is invalid or empty: load a new asset from the global resource
    loadAssetFromResource(&g_globalResource, (void*)((uintptr_t)thisPtr + 0x3C), g_someParameter, 0, 4);
}