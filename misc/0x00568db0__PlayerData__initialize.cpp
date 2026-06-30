// FUNC_NAME: PlayerData::initialize
int PlayerData::initialize(int playerId, int param2, int param3, int param4, const char* displayName)
{
    char languageCode[256];
    char defaultName[256];
    char finalName[256];
    char finalDisplayName[256];
    char* defaultNamePtr = nullptr;
    int nameBuffer = 0;
    int nameBufferSize = 0;
    void (*nameDeallocator)(int) = nullptr;

    // Clear buffers
    finalName[0] = '\0';
    memset(finalName + 1, 0, 0xFF);
    finalDisplayName[0] = '\0';
    memset(finalDisplayName + 1, 0, 0xFF);

    // Process param3 (likely language or locale ID)
    FUN_004d3bc0(param3);

    // Get localized string (e.g., player name from language settings)
    const char* localizedString = FUN_004d58c0();
    snprintf(finalDisplayName, 0x100, "%s", localizedString);

    // If there's a previous name buffer, possibly truncate it
    if (nameBufferSize != 0) {
        uint len = FUN_004d4e20(nameBuffer);
        if ((len != 0) && (nameBuffer < len)) {
            FUN_004d3c40(nameBuffer, len - nameBuffer);
            goto LAB_00568e6b;
        }
    }

    defaultNamePtr = nullptr;

LAB_00568e6b:
    // Copy global static string into finalName
    FUN_004d4c00(g_StaticNameBuffer, g_StaticNameBuffer); // probably updates g_StaticNameBuffer
    const char* source = defaultNamePtr;
    if (defaultNamePtr == nullptr) {
        source = &DEFAULT_NAME_STRING; // e.g., "Unnamed"
    }
    snprintf(finalName, 0x100, "%s", source);

    // Allocate new PlayerData object
    PlayerData* obj = (PlayerData*)FUN_00568fb0();
    if (obj == nullptr) return 0;

    // Fill fields
    obj->field_0x120 = param2;          // +0x120: some flag or type
    strncpy(obj->nameBuffer, finalName, 0x80); // +0x08: name (128 bytes)
    obj->nameNullTerminator = '\0';     // +0x87: ensure null terminator for 0x80-length buffer
    obj->field_0x10c = playerId;        // +0x10c: player ID
    strncpy(obj->displayName, finalDisplayName, 0x80); // +0x88: display name
    obj->displayNameNullTerminator = '\0'; // +0x107
    obj->field_0x108 = param4;          // +0x108: some parameter

    // Copy displayName string to offset +0x110 (overlapping? same as displayName? Actually separate)
    char* dest = &obj->bufferAt0x110;   // +0x110
    while (*displayName != '\0') {
        *dest = *displayName;
        displayName++;
        dest++;
    }
    *dest = '\0';

    // Cleanup
    if (defaultNamePtr != nullptr) {
        (*(void (*)(char*))0x0)(defaultNamePtr); // free or deallocate
    }
    if (nameBuffer != 0) {
        (*nameDeallocator)(nameBuffer);
    }

    return (int)obj;
}