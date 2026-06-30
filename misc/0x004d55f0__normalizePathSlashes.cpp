// FUNC_NAME: normalizePathSlashes
// Address: 0x004d55f0
// Role: Converts all forward slashes ('/') to backslashes ('\\') in a string buffer.
// The buffer is described by a struct containing a pointer to the string and its length.
// This is a common path normalization function for Windows file systems.

struct StringBuffer {
    char* data;      // +0x00: pointer to character array
    uint32_t length; // +0x04: number of characters in the buffer
};

void __fastcall normalizePathSlashes(StringBuffer* buffer)
{
    uint32_t i = 0;
    if (buffer->length != 0) {
        do {
            if (buffer->data[i] == '/') {
                buffer->data[i] = '\\';
            }
            i++;
        } while (i < buffer->length);
    }
}