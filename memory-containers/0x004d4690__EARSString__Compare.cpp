// FUNC_NAME: EARSString::Compare
int __thiscall EARSString::Compare(const wchar_t* other) {
    bool bOtherNonEmpty;
    wchar_t* pThisChar;
    wchar_t cThis, cOther;

    // Check if the other string is null or empty
    if (other == nullptr || *other == 0) {
        bOtherNonEmpty = false;
    } else {
        bOtherNonEmpty = true;
    }

    // If this string's length field is zero, return whether other is non-empty
    if (this->m_nLength == 0) {
        return bOtherNonEmpty ? 1 : 0;
    }

    // If this string has nonzero length but other is empty, return -1
    if (!bOtherNonEmpty) {
        return -1;
    }

    // Compare wide characters (2 bytes each) in lexicographic order
    pThisChar = this->m_pString;
    while (true) {
        cThis = *pThisChar;
        cOther = *other;

        // Compare low bytes first (little-endian)
        if (cThis != cOther) {
            // Return -1 if this char is less, 1 if greater
            return (cThis < cOther) ? -1 : 1;
        }

        // If both zero, strings are equal
        if (cThis == 0) {
            return 0;
        }

        // Compare high bytes
        cThis = *(pThisChar + 1);
        cOther = *(other + 1);
        if (cThis != cOther) {
            return (cThis < cOther) ? -1 : 1;
        }

        pThisChar += 2;
        other += 2;

        // If high byte is zero (end of wide string after null), strings equal
        if (cThis == 0) {
            return 0;
        }
    }
}