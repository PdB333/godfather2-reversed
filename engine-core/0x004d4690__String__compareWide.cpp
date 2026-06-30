// FUNC_NAME: String::compareWide
uint __thiscall String::compareWide(const wchar_t* other) {
    // Structure: this->stringPtr (offset 0), this->length (offset 4)
    bool otherNonEmpty;
    if (other == nullptr || *other == L'\0') {
        otherNonEmpty = false;
    } else {
        otherNonEmpty = true;
    }

    // If this string length is zero, return whether other is non-empty (0 or 1)
    if (this->length == 0) {
        return (uint)otherNonEmpty;
    }

    // If other is null or empty, return -1
    if (!otherNonEmpty) {
        return 0xffffffff;
    }

    // Compare as two-byte (wide character) chunks, byte-by-byte in little-endian order
    const unsigned char* thisChars = (const unsigned char*)this->stringPtr;
    const unsigned char* otherChars = (const unsigned char*)other;
    bool lessThan;

    while (true) {
        unsigned char lowThis = *thisChars;
        unsigned char lowOther = *otherChars;
        lessThan = (lowThis < lowOther);
        if (lowThis != lowOther) break;
        if (lowThis == 0) {
            // End of string (low byte null implies null character)
            return 0;
        }

        unsigned char highThis = thisChars[1];
        unsigned char highOther = otherChars[1];
        lessThan = (highThis < highOther);
        if (highThis != highOther) break;
        thisChars += 2;
        otherChars += 2;
        if (highThis == 0) {
            // End of string (high byte null after low non-null? Follows decompiled logic)
            return 0;
        }
    }

    // Convert boolean to -1 or 1
    return (1 - (uint)lessThan) - (uint)(lessThan != 0);
}