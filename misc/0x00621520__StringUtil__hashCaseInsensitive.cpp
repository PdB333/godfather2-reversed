// FUNC_NAME: StringUtil::hashCaseInsensitive
// Function address: 0x004dafd0 (thunk at 0x00621520)
// EA EARS engine string hashing utility, case-insensitive variant.
// Used for fast string lookup mapping (e.g., object names, resource identifiers).
// Algorithm: djb2-style hash with case folding for A-Z.

int hashCaseInsensitive(const char* str) {
    int hash = 0;
    if (str != nullptr) {
        char c = *str;
        while (c != '\0') {
            unsigned int uChar = (unsigned int)(unsigned char)c;
            // Fold uppercase letters to lowercase (ASCII A-Z -> a-z)
            if (uChar - 0x41 < 0x1a) { // between 'A' and 'Z' inclusive
                uChar += 0x20; // convert to lowercase
            }
            // hash = hash * 0x1003f + character
            hash = hash * 0x1003f + uChar;
            c = *(++str);
        }
    }
    return hash;
}