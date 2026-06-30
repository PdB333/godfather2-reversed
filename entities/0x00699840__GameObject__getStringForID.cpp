// FUNC_NAME: GameObject::getStringForID
uint __thiscall GameObject::getStringForID(int this, uint id, char *outBuffer, size_t bufferSize)
{
    char *source = nullptr;
    *outBuffer = '\0'; // Clear output buffer

    // Lookup ID in string table. The function may modify outBuffer pointer (likely to source string)
    int *pResult = (int *)stringTableLookup(&outBuffer, id);

    if (*pResult == this + 4) {
        // If the ID matches this object's class ID at offset +0x04, return false (0)
        outBuffer = (char *)((uintptr_t)outBuffer & 0xFFFFFF00);
    } else {
        // Resolve string from table entry at offset +0x20
        resolveString(*pResult + 0x20);

        // Use default string if source is null (always true in this path)
        source = nullptr;
        if (source == nullptr) {
            source = &s_defaultString; // DAT_0120546e
        }

        strncpy(outBuffer, source, bufferSize);
        outBuffer[bufferSize - 1] = '\0';

        // Set low byte to 1 for return value (true)
        outBuffer = (char *)(((uintptr_t)outBuffer & 0xFFFFFF00) | 1);
    }

    // Dead code: if (source != nullptr) (*(code*)0x0)(source, source, 0, 0); // debug assert?
    return (uintptr_t)outBuffer & 0xFF; // Return low byte: 0 = match, 1 = string copied
}