// FUNC_NAME: EA::FilePath::getBasename
// Address: 0x004d58c0
// Role: Extracts filename (basename) from a stored path string.
// The class has two fields:
//   +0x00: char* mPath (pointer to path string)
//   +0x04: int   mLength (string length, not including null terminator)
// If the path ends with '\\' or '/', returns a static empty string (possibly ".").
// If no separator found, returns the original path.
// Otherwise returns pointer to first character after the last separator.

char* __thiscall EA::FilePath::getBasename(void) {
    int length = *(int*)((char*)this + 4);  // +0x04
    if (length != 0) {
        char* path = *(char**)this;         // +0x00
        char* last = path + length - 1;

        // Check if the last character is a slash or backslash
        if (*last != '/' && *last != '\\') {
            // Search backwards for a separator
            while (last >= path) {
                if (*last == '/' || *last == '\\') {
                    return last + 1;  // pointer to character after separator
                }
                last--;
            }
            // No separator found – return the whole path
            return path;
        }
    }
    // Empty or root path – return static placeholder (e.g., "." or empty string)
    return &DAT_0120546e;
}