// FUNC_NAME: UILocalizedText::setTextFromIds
void __thiscall UILocalizedText::setTextFromIds(int thisPtr, char* destName, char* destDesc, int param4)
{
    char* stringBuf = nullptr;
    void* freeFunc = nullptr; // likely destructor placeholder
    int unused = 0;

    // Get name string from the first ID (offset +0x14)
    StringTable::getString(*(uint*)(thisPtr + 0x14), &stringBuf, 1);
    char* namePtr = stringBuf;
    if (namePtr == nullptr) {
        namePtr = &DAT_0120546e; // default fallback string (empty or placeholder)
    }
    // Copy/set the name into destination
    StringUtils::setString(destName, namePtr, param4, unused);

    // Get description string from the second ID (offset +0x54)
    StringTable::getString(*(uint*)(thisPtr + 0x54), &stringBuf, 1);
    namePtr = stringBuf;
    if (namePtr == nullptr) {
        namePtr = &DAT_0120546e;
    }
    StringUtils::setString(destDesc, namePtr, param4, unused);

    // If the buffer was allocated, release it via function pointer (likely a destructor)
    if (stringBuf != nullptr) {
        // Note: freeFunc is always 0 here in decompiled output; actual code may set it from a vtable or similar
        (*freeFunc)(stringBuf);
    }
}