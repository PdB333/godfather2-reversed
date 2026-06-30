// FUNC_NAME: normalizePathSeparators
// Address: 0x004d55d0
// Replaces all backslashes ('\\') with forward slashes ('/') in a path buffer.
// The buffer is provided as a structure: [data pointer, length].
// This is a utility function commonly used for path normalization in the EA EARS engine.

void __fastcall normalizePathSeparators(int* pathBuffer)
{
    unsigned int index = 0;
    
    // Check if the buffer length is non-zero.
    if (pathBuffer[1] != 0)
    {
        do
        {
            // If the current character is a backslash, replace it with a forward slash.
            if (*(char*)(pathBuffer[0] + index) == '\\')
            {
                *(char*)(pathBuffer[0] + index) = '/';
            }
            index++;
        } while (index < (unsigned int)pathBuffer[1]);
    }
    
    return;
}