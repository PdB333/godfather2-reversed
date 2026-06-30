// FUNC_NAME: FilePath::getFileName
// Function at 0x004d58c0: Extracts the filename portion from a path string.
// The object has a char* buffer at offset 0 and an int length at offset 4.
// Returns a pointer into the original buffer (or a global empty string if path ends with slash).
char* FilePath::getFileName() const {
    int len = this->length;  // +0x04
    if (len != 0) {
        char* str = this->buffer;  // +0x00
        char* lastChar = str + len - 1;
        // If the last character is not a slash, scan backwards for one.
        if (*lastChar != '\\' && *lastChar != '/') {
            char* p = lastChar;
            while (p >= str) {
                if (*p == '\\' || *p == '/') {
                    return p + 1;
                }
                p--;
            }
            // No slash found; return the whole string.
            return str;
        }
    }
    // Path ends with a slash or is empty; return a global empty string.
    return &DAT_0120546e;  // global empty string
}