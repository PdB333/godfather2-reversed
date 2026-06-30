// FUN_004d53a0: EARSString::trim(char)
// 
// Trims occurrences of character 'ch' from the beginning and end of the string.
// The string is stored as a buffer with a length field (no null termination assumed initially).
// After trimming, the result is copied to the start of the buffer and null-terminated.
// If trimming results in an empty string, length becomes 0 and buffer[0] = '\0'.
// An error handler is called if the internal pointers cross (shouldn't happen).

void __thiscall EARSString::trim(char ch)
{
    char* buffer = this->bufferPtr;        // [0x00] char* buffer
    int& length = this->length;            // [0x04] int length

    if (length != 0)
    {
        char* src = buffer;
        char c = *src;

        // Scan forward while characters match ch
        while (c == ch)
        {
            ++src;
            c = *src;
        }

        char* dstEnd = buffer + length;
        char* pcVar2 = dstEnd;
        char cLast = pcVar2[-1];           // last character

        // Scan backward while characters match ch
        while (cLast == ch)
        {
            --pcVar2;
            cLast = pcVar2[-1];
        }

        int newLength = pcVar2 - src;
        if (newLength < length)
        {
            if (pcVar2 < src)
            {
                // Safety check: if pointers crossed, something went wrong
                // This is likely an assert or error handler
                FUN_00401060();             // error / assertion
                return;
            }

            length = newLength;
            memcpy(buffer, src, newLength);
            buffer[length] = '\0';          // null-terminate
        }
    }
}