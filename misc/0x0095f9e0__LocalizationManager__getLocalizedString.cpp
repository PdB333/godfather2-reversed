// FUNC_NAME: LocalizationManager::getLocalizedString
void __thiscall LocalizationManager::getLocalizedString(int thisPtr, char* outBuffer)
{
    uint* stringIndex;
    char* sourceString;
    
    // Initialize or update localization state (e.g., load current language)
    SomeInitFunction(); // FUN_0095ecd0
    
    uint currentIndex = *(uint*)(thisPtr + 0x18); // m_currentLanguageIndex or similar
    if (currentIndex < g_localizedStringCount) // DAT_0113085c
    {
        // Table entry at g_localizedStringTable + (index * 0x10)
        // Each entry: [0] pointer to string, [4] some ID/hash
        uint entryOffset = currentIndex * 0x10 + g_localizedStringTable; // DAT_01130858
        uint* entry = (uint*)entryOffset;
        sourceString = (char*)*entry;
        if (sourceString == nullptr)
        {
            sourceString = &DAT_0120546e; // default empty string placeholder
        }
        // Copy source string to output buffer (max 0x80 bytes), entry[1] is likely hash or flags
        SafeStringCopy(outBuffer, sourceString, 0x80, entry[1]); // FUN_005c4660
        return;
    }
    // Out of bounds: null-terminate the buffer
    *outBuffer = 0;
}