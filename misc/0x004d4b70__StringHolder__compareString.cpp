// FUNC_NAME: StringHolder::compareString
// Address: 0x004d4b70
// Compares the object's stored string (m_string) with a given string, with null handling.
// Returns 0 if equal, negative if m_string < otherString, positive if m_string > otherString.
// If m_hasString is zero, returns 1 if otherString is non-empty, else 0 (treats empty as equal).
// If m_hasString is non-zero and otherString is empty, returns 0xFFFFFFFF (sentinel).

uint __thiscall StringHolder::compareString(const char* otherString)
{
    bool bOtherNonEmpty;
    char* thisStr;
    bool bCmpResult;
    uint result;

    // Check if otherString is not null and not empty
    if ((otherString == (char*)0x0) || (*otherString == '\0')) {
        bOtherNonEmpty = false;
    } else {
        bOtherNonEmpty = true;
    }

    // m_hasString field at this+0x04
    if (*(int*)((uint)this + 4) != 0) {
        if (bOtherNonEmpty) {
            thisStr = *(char**)this; // m_string at this+0x00
            if ((thisStr != (char*)0x0) && (otherString != (char*)0x0)) {
                // Both strings exist: case-insensitive compare
                result = __stricmp(thisStr, otherString);
                return result;
            }
            // thisStr is null while otherString is non-null
            // Pointer comparison: null is considered less than any valid address
            if (thisStr <= otherString) {
                // Since thisStr is 0, this is always true; returns 1 (thisStr < otherString)
                return (uint)(thisStr < otherString);
            }
        }
        // Either otherString is empty (bOtherNonEmpty false) or thisStr > otherString (unreachable)
        return 0xffffffff;
    }

    // m_hasString == 0: object has no string
    // Return 1 if otherString is non-empty (no match), 0 if empty (match)
    return (uint)bOtherNonEmpty;
}