// FUNC_NAME: String::compare
// Address: 0x004d4b20
// Role: Compares two String objects (case-insensitive). Returns negative if this < other, 0 if equal, positive if this > other.
// Ordering: Invalid strings (mFlags == 0) are considered greater than valid strings. Among valid, uses __stricmp on mData pointers.

class String {
public:
    char* mData;   // +0x00: pointer to character data
    int   mFlags;  // +0x04: 0 = invalid/empty, non-zero = valid
};

int __thiscall String::compare(const String& other) const {
    // If this string is invalid (mFlags == 0), compare based on other's validity
    if (this->mFlags == 0) {
        // Return 1 if other is valid, 0 if both invalid
        return (other.mFlags != 0) ? 1 : 0;
    }

    // If other string is valid, perform string comparison
    if (other.mFlags != 0) {
        const char* thisStr = this->mData;
        const char* otherStr = other.mData;

        // Both have non-null data pointers -> standard case-insensitive compare
        if (thisStr != nullptr && otherStr != nullptr) {
            return __stricmp(thisStr, otherStr);
        }

        // One or both data pointers are null (should not happen if flags indicate valid)
        // Treat null as greater than non-null, and equal if both null
        if (thisStr <= otherStr) {
            return (thisStr < otherStr) ? 1 : 0;
        }
        // thisStr > otherStr -> return -1
        return -1;
    }

    // this is valid, other is invalid -> this < other
    return -1;
}