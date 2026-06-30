// FUNC_NAME: hashStringCaseInsensitive
// Function at 0x004dafd0: Simple case-insensitive string hash (multiplier 0x1003f = 65599)
// Used extensively for string lookups (e.g., asset names, identifiers)
int hashStringCaseInsensitive(const byte* str)
{
    int hash = 0;
    if (str != nullptr) {
        byte ch = *str;
        while (ch != 0) {
            uint c = (uint)ch;
            str++;
            // Convert uppercase ASCII letters (A-Z) to lowercase
            if (c - 0x41 < 0x1a) { // 'A' to 'Z'
                c = c + 0x20;      // to lowercase
            }
            // Classic hash: hash * 65599 + character
            hash = hash * 0x1003f + (int)c;
            ch = *str;
        }
    }
    return hash;
}