// FUNC_NAME: DebugLogBuffer::addEntry
int __thiscall DebugLogBuffer::addEntry(char* str1, char* str2, char* str3, char* str4)
{
    // Offset from this: +0xA4 = current write index (int)
    int index = this->m_currentIndex;
    // Offset from this: +0xAC = base pointer to buffer array (entry size 0x61)
    char* dest = this->m_bufferBase + index * 0x61;
    this->m_currentIndex = index + 1;

    // Copy first string (max 31 characters) to offset 0x00
    int offset = 0;
    if (str1 != nullptr && *str1 != '\0') {
        _strncpy(dest, str1, 0x1f);
        offset = 0x1f;
    }
    dest[offset] = '\0';

    // Copy second string (max 31 characters) to offset 0x20
    offset = 0;
    if (str2 != nullptr && *str2 != '\0') {
        _strncpy(dest + 0x20, str2, 0x1f);
        offset = 0x1f;
    }
    dest[0x20 + offset] = '\0';

    // Copy third string (max 31 characters) to offset 0x40
    offset = 0;
    if (str3 != nullptr && *str3 != '\0') {
        _strncpy(dest + 0x40, str3, 0x1f);
        offset = 0x1f;
    }
    dest[0x40 + offset] = '\0';

    // Set boolean flag at offset 0x60; true unless str4 == "0"
    if (str4 != nullptr) {
        dest[0x60] = (__stricmp(str4, "0") != 0);
    } else {
        dest[0x60] = true;
    }

    return index;
}