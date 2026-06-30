// FUNC_NAME: normalizePathSeparators
// Function at 0x004d55f0: replaces all '/' with '\\' in a path string buffer (in-place).
void __fastcall normalizePathSeparators(int* pathInfo)
{
    char* buffer = (char*)pathInfo[0];     // +0x00: pointer to string buffer
    unsigned int length = pathInfo[1];      // +0x04: length of string

    if (length != 0) {
        for (unsigned int i = 0; i < length; i++) {
            if (buffer[i] == '/') {
                buffer[i] = '\\';
            }
        }
    }
    return;
}